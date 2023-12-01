//****************************************************************************
//*  Copyright (c) Federal University of Para, brazil - 2011                 *
//*  Developed at the Research Group on Computer Network and Multimedia      *
//*  Communication (GERCOM)     				             *
//*  All rights reserved    				                     *
//*                                                                          *
//*  Permission to use, copy, modify, and distribute this protocol and its   *
//*  documentation for any purpose, without fee, and without written         *
//*  agreement is hereby granted, provided that the above copyright notice,  *
//*  and the author appear in all copies of this protocol.                   *
//*                                                                          *
//*  Module:   LEACH Clustering Protocol for Castalia Simulator              *
//*  Version:  0.2                                                           *
//*  Author(s): Adonias Pires <adonias@ufpa.br>                              *
//*             Claudio Silva <claudio.silva@itec.ufpa.br>                   *
//****************************************************************************/

#include "VirtualRingRouting.h"

Define_Module(VirtualRingRouting);

void VirtualRingRouting::startup()
{	
	/*--- The .ned file's parameters ---*/
	percentage = par("percentage");
	roundLength = par("roundLength");
	isSink = par("isSink");
	slotLength = par("slotLength");
	advPacketSize = par("advPacketSize");
	joinPacketSize = par("joinPacketSize");
	tdmaPacketSize = par("tdmaPacketSize");
	dataPacketSize = par("dataPacketSize");
	applicationID = par("applicationID").stringValue(); 

	/*--- Class parameters ---*/
	CHcandidates.clear();
	clusterMembers.clear();
	roundNumber=0;
	probability = 0;
	
	isCH = false;
	endFormClus = false;
	isCt = false;
	// Virtual ring parameters
	sinkRssi = 0;
	NeighborsTable.clear();
				
	// residualEnergy = resMgrModule->getRemainingEnergy(); // to retrieve the residual energy of the node
	// int rand();

	/*--- Node location --- */
	cModule *parentParent = getParentModule()->getParentModule();
	if (parentParent->findSubmodule("MobilityManager") != -1) {
	  VirtualMobilityManager* mobilityModule = check_and_cast <VirtualMobilityManager*>(parentParent->
		getSubmodule("MobilityManager"));
	  varX = mobilityModule->getLocation().x;
	  varY = mobilityModule->getLocation().y;
	  varZ = mobilityModule->getLocation().z;
	  trace() << "[Location](" << varX << ", " << varY << ", " << varZ << ")";
	}

	//VirtualMobilityManager* mobilityModule = check_and_cast <VirtualMobilityManager*>(parentParent-> getSubmodule("MobilityManager"));
	readXMLparams();
		
	setTimer(DISCOVERY_ROUND, 1.0); // All the node start the World discovery even the Sink
	/*
	if (isSink) {
		RingNeighborsTable.clear();
		setTimer(HELLO_WORLD, 5.0); // sink Node sends hello word
	} else 
		setTimer(DISCOVERY_ROUND, 1.0);
	*/
	// if(!isSink) setTimer(DISCOVERY_ROUND, 0);

	/* Node resource manager */ 
	resourceModule = check_and_cast <ResourceManager*>(parentParent->getSubmodule("ResourceManager"));

	/* XXX-albarc 18/07/17 Slots extra determinados por el campo de nivel de prioridad en el paquete de JOIN */
	myPriorityLevel = par("myPriorityLevel");
	priorityLevelsVector.clear();
	slotsIncreasePercentagePriorityLevel_1 = par("slotsIncreasePercentagePriorityLevel_1");
	slotsIncreasePercentagePriorityLevel_2 = par("slotsIncreasePercentagePriorityLevel_2");

	// Rellenar los vectores de priority sources para los collectOutput
	priorityLevel_1_Sources = par("priorityLevel_1_Sources");
	cStringTokenizer tokenizer(priorityLevel_1_Sources);
	while (tokenizer.hasMoreTokens()) {
		priorityLevel_1_SourcesVector.push_back(atoi(tokenizer.nextToken()));
	}

	priorityLevel_2_Sources = par("priorityLevel_2_Sources");
	cStringTokenizer tokenizer2(priorityLevel_2_Sources);
	while (tokenizer2.hasMoreTokens()) {
		priorityLevel_2_SourcesVector.push_back(atoi(tokenizer2.nextToken()));
	}

	/*--- XXX-albarc Trazas sobre datos de la simulación ---*/
	if(isSink) {	// Para que no salgan en todos
		trace() << "##### DATOS DE LA SIMULACIÓN #####";
		trace() << "##### Tiempo de simulación: " <<  ev.getConfig()->getConfigValue("sim-time-limit") << " #####";

		cModule *sensorNetwork = getParentModule()->getParentModule()->getParentModule();
		if (sensorNetwork != NULL) {
			int x_dim = sensorNetwork->par("field_x");
			int y_dim = sensorNetwork->par("field_y");
			int z_dim = sensorNetwork->par("field_z");
			numNodes = sensorNetwork->par("numNodes");
			trace() << "##### Dimensiones del escenario: (" << x_dim << ", " << y_dim << ", " << z_dim << ") #####";
			trace() << "##### Número total de nodos: " << numNodes << " #####";
		}

		trace() << "##### LEACH Round length: " << roundLength << " s #####";
		trace() << "##### LEACH Slot length: " << slotLength << " s #####";
		trace() << "##### LEACH Percentage: " << percentage << "% #####";

		for (std::vector<int>::const_iterator i = priorityLevel_1_SourcesVector.begin(); i != priorityLevel_1_SourcesVector.end(); ++i) {
			int pos = i - priorityLevel_1_SourcesVector.begin();
			trace() << "##### LEACH Priority Level 1 Sources: " << *i << " #####";
		}

		for (std::vector<int>::const_iterator i = priorityLevel_2_SourcesVector.begin(); i != priorityLevel_2_SourcesVector.end(); ++i) {
			int pos = i - priorityLevel_2_SourcesVector.begin();
			trace() << "##### LEACH Priority Level 2 Sources: " << *i << " #####";
		}
	}

	sizeSchedule = 0;
	delayBetweenPacketsEnabled = par("delayBetweenPacketsEnabled");
	delayBetweenPackets = par("delayBetweenPackets");

	// Preparar recolección para CastaliaResults
	totalPacketsReceived = 0;
	totalRegularPacketsReceived = 0;
	declareOutput("[LEACH] Aggregated Packets received at the sink from CH");
	declareOutput("[LEACH] Individual packets received at the sink per node");
	declareOutput("[LEACH] Regular packets received at the sink per source");
	declareOutput("[LEACH] Total regular packets received at the sink");
	declareOutput("[LEACH] Individual packets sent");

	// Niveles de prioridad
	totalPriorityLevel_1_PacketsReceived = 0;
	totalPriorityLevel_2_PacketsReceived = 0;
	declareOutput("[LEACH] Priority level 1 packets received at the sink per source");
	declareOutput("[LEACH] Total priority level 1 packets received at the sink");
	declareOutput("[LEACH] Priority level 2 packets received at the sink per source");
	declareOutput("[LEACH] Total priority level 2 packets received at the sink");

	// Medir latencia según prioridad
	totalLatencyOfAllPackets = 0;
	totalLatencyOfPL1Packets = 0;
	totalLatencyOfPL2Packets = 0;
	totalLatencyOfRegularPackets = 0;

	declareOutput("[LEACH] Individual aggregated latency of node 43");
	declareOutput("[LEACH] Received packets of node 43");
	totalLatencyOfNode43Packets = 0;
	totalNode43PacketsReceived = 0;

	// Histograma para medir los paquetes recibidos por buckets	y la energía gastada en cada uno
	simTimeLimit = atoi(ev.getConfig()->getConfigValue("sim-time-limit"));
	numTimeBuckets = par("numTimeBuckets");
	timeBucketDuration = (int) simTimeLimit / numTimeBuckets;
	declareHistogram("[LEACH] Histogram of received packets of node 43", 0, simTimeLimit, numTimeBuckets);
	declareOutput("[LEACH] Energy consumption per bucket of node 43");
	energyConsumedInTimeBucket = 0;
	currentTimeBucket = 0;

	string node43 = "43";
	if (node43.compare(SELF_NETWORK_ADDRESS)) {
		/*--- Node resource manager ---*/
		if (parentParent->findSubmodule("ResourceManager") != -1) {
		  resourceModule = check_and_cast <ResourceManager*>(parentParent->getSubmodule("ResourceManager"));
		}

		setTimer(COUNTER_ENERGY_MONITORING, 0);
	}

	// PRUEBA MINISLOTS
	slot = 0;
	miniSlot = 0;
}

void VirtualRingRouting::fromApplicationLayer(cPacket *pkt, const char *destination)
{	
	if(!isSink)
	{
		string dst(destination);
		VirtualRingRoutingPacket *netPacket = new VirtualRingRoutingPacket("Leach routing data packet", NETWORK_LAYER_PACKET);
		netPacket->setVirtualRingRoutingPacketKind(LEACH_ROUTING_DATA_SINGLE_PACKET);
		netPacket->setByteLength(dataPacketSize);
		netPacket->setSource(SELF_NETWORK_ADDRESS);
		encapsulatePacket(netPacket, pkt);
		if (!isCH && endFormClus)
		{
			CHInfo info = *CHcandidates.begin();
			stringstream buffer;
			buffer << info.src;
			string dst = buffer.str();
			netPacket->setDestination(dst.c_str());	
			bufferPacket(netPacket);
		}	
		else if (!isCH && !endFormClus) 
		{
			tempTXBuffer.push(netPacket);
		}
		else if (isCH) 
		{
			bufferAggregate.push_back(*netPacket);
		}
	}		
}

void VirtualRingRouting::fromMacLayer(cPacket *pkt, int macAddress, double rssi, double lqi){
	VirtualRingRoutingDscvPacket *netPacket = dynamic_cast <VirtualRingRoutingDscvPacket*>(pkt);

	if (!netPacket)
		return;

	switch (netPacket->getVirtualRingRoutingPacketKind()) {
		
		/* The hello world packet sent by the Sink is received */
		case HELLO_WORD_PACKET:{ 
			// Wake up and start the Neighbor discovery 
			sinkRssi = rssi ;
			trace() << "Node : " << self << " receives hello packt from : " << macAddress << "with the RSSI :  " << rssi;
			break;	
		}
		
		case BROADCAST_PACKET:{ 
			// Build the neighbor table "Neighbors"
			NeighborInfo neighbor;
			neighbor.src = atoi(netPacket->getSource());
			neighbor.rssi = rssi;
			neighbor.residual = netPacket->getResidual();
			neighbor.location[0] = netPacket->getLocation(0); neighbor.location[1] = netPacket->getLocation(1); neighbor.location[2] = netPacket->getLocation(2);
			if ((atoi(netPacket->getSource()) == 0) && (self != 0 )) {
				isSinkNeighbor = 1;
				trace() << "Node : " << self << " is a 1-hop neighbor of the sink node ";
			}
			NeighborsTable.push_back(neighbor);
			trace() << "Node : " << self << " receives hello packt from : " << atoi(netPacket->getSource()) << " with the RSSI :  " << rssi << ", and there is :" << NeighborsTable.size() << " Inside the neighbor table";
			// double timer = uniform (15.0, 18.0);
			// setTimer(SEND_DATA_TO_SINK, timer); // Wait few seconds in order to receive the overall request
			break;	
		}
		
		case LEACH_ROUTING_DATA_SINGLE_PACKET:{
			string dst(netPacket->getDestination());
			string src(netPacket->getSource());
			long size = (long)netPacket->getByteLength();
			int num(netPacket->getSequenceNumber());
			if (isCH && dst.compare(SELF_NETWORK_ADDRESS) == 0){
				// XXX-albarc Ver como se agregan los paquetes en los CH
				trace() << "Soy el CH " << self << ", recibido paquete de " << src
					<< " con " << size << " bytes y seqNum " << num;
				//trace() << "Node " << self << " Aggregate Data Frame \n";
				bufferAggregate.push_back(*netPacket);
			}
			break;
		}
		case LEACH_ROUTING_DATA_AGGREGATED_PACKET:{
			VirtualRingRoutingDataAggregatedPacket *aggrPacket = dynamic_cast <VirtualRingRoutingDataAggregatedPacket*>(netPacket);
			string dst(aggrPacket->getDestination());
			string src(aggrPacket->getSource());
			long size = (long)aggrPacket->getByteLength();
			int num(aggrPacket->getSequenceNumber());
			
			if (dst.compare(SINK_NETWORK_ADDRESS) == 0 && isSink) {
				// XXX-albarc Ver como es el paquete agregado al llegar al sink
				//trace() << "Node " << self << " Processing Data Packet";

				trace() << "[LEACH] Received aggregated packet from ClusterHead " << src << " with " << size << " bytes and seqNum " << num;

				// Aquí los collectOutput para paquetes agregados, individuales
				collectOutput("[LEACH] Aggregated Packets received at the sink from CH", src.c_str());

				// Desagregar el paquete cogiendo la source, el seqNum y el timestamp del momento del envío.
				vector<int> sourcesList;
				vector<int> seqNumList;
				vector<simtime_t> creationTimestampList;
				for (unsigned int i = 0; i < aggrPacket->getIndivSourcesArraySize(); i++)
				{
					sourcesList.push_back(aggrPacket->getIndivSources(i));
					seqNumList.push_back(aggrPacket->getIndivSeqNum(i));
					creationTimestampList.push_back(aggrPacket->getIndivCreationTimestamp(i));
				}

				int indivSource;
				int seqNum;
				simtime_t creationTimestamp;
				double latencyInS;
				int currentTime;
				while (!sourcesList.empty())
				{
					indivSource = sourcesList.back();
					sourcesList.pop_back();

					seqNum = seqNumList.back();
					seqNumList.pop_back();

					creationTimestamp = creationTimestampList.back();
					creationTimestampList.pop_back();

					latencyInS = SIMTIME_DBL(simTime() - creationTimestamp);

					collectOutput("[LEACH] Individual packets received at the sink per node", indivSource);
					totalPacketsReceived++;

					totalLatencyOfAllPackets += latencyInS;

					if (indivSource == 43) {
						collectOutput("[LEACH] Individual aggregated latency of node 43","",latencyInS);
						collectOutput("[LEACH] Received packets of node 43");

						totalLatencyOfNode43Packets += latencyInS;
						totalNode43PacketsReceived++;

						currentTime = (int) SIMTIME_DBL(simTime());
						trace() << "[LEACH] SINK Received packet from node 43 at time: " << currentTime;

						if (simTimeLimit > 0 && numTimeBuckets > 0) {
							collectHistogram("[LEACH] Histogram of received packets of node 43", currentTime);
						}
					}

					if (isPriorityLevelSource(indivSource, 1)) {
						trace() << "[LEACH] Received packet #" << seqNum << " from PRIORITY LEVEL 1 source " << indivSource
							<< " via ClusterHead " << src << ", con latencia " << latencyInS << " s";

						collectOutput("[LEACH] Priority level 1 packets received at the sink per source", indivSource);
						collectOutput("[LEACH] Total priority level 1 packets received at the sink");
						totalPriorityLevel_1_PacketsReceived++;

						totalLatencyOfPL1Packets += latencyInS;

					} else if (isPriorityLevelSource(indivSource, 2)) {
						trace() << "[LEACH] Received packet #" << seqNum << " from PRIORITY LEVEL 2 source " << indivSource
							<< " via ClusterHead " << src << ", con latencia " << latencyInS << " s";

						collectOutput("[LEACH] Priority level 2 packets received at the sink per source", indivSource);
						collectOutput("[LEACH] Total priority level 2 packets received at the sink");
						totalPriorityLevel_2_PacketsReceived++;

						totalLatencyOfPL2Packets += latencyInS;
					} else {
						trace() << "[LEACH] Received packet #" << seqNum << " from PRIORITY LEVEL 3 source " << indivSource
							<< " via ClusterHead " << src << ", con latencia " << latencyInS << " s";
						// Media más "real" solo contando los no prioritarios
						collectOutput("[LEACH] Regular packets received at the sink per source", indivSource);
						collectOutput("[LEACH] Total regular packets received at the sink");
						totalRegularPacketsReceived++;

						totalLatencyOfRegularPackets += latencyInS;
					}

					// XXX-albarc Mandar aquí un appPacket por cada una de las sources
					ApplicationPacket *newPacket = new ApplicationPacket("App generic packet", APPLICATION_PACKET);
					newPacket->setData(0);
					newPacket->getAppNetInfoExchange().destination = string("0");
					newPacket->getAppNetInfoExchange().source = to_string(indivSource);	// Source del paquete individual, salvado en un campo del paquete agregado.
					newPacket->setSequenceNumber(seqNum);	// SeqNum del paquete individual, salvado en un campo del paquete agregado
					newPacket->getAppNetInfoExchange().timestamp = creationTimestamp;	// Timestamp de la creación original del paquete, salvado en un campo del paquete agregado
					newPacket->setApplicationID(applicationID.c_str());
					toApplicationLayer(newPacket);
				}

			}
			break;
		}
		case LEACH_ROUTING_ADV_PACKET:{

			if(!isCH && !isSink)
			{
				//trace() << "Node " << self << " Received a Advertisement Message of node " << netPacket->getSource() << " with RSSI: " << rssi << "\n";	
				CHInfo rec;
				rec.src = atoi(netPacket->getSource());
				rec.rssi = rssi;
				CHcandidates.push_front(rec);
			}
			break;
		}
		case LEACH_ROUTING_JOIN_PACKET:{
			VirtualRingRoutingJoinPacket *joinPacket = dynamic_cast <VirtualRingRoutingJoinPacket*>(netPacket);
			string dst(joinPacket->getDestination());
			string source = joinPacket->getSource();
			int currentPriorityLevel = joinPacket->getPriorityLevel();
			if(isCH && dst.compare(SELF_NETWORK_ADDRESS) == 0) {
				trace() << "CH Node " << self << " Received JOIN msg from " << source << " with priorityLevel " << currentPriorityLevel;
				//trace() << "Node " << self << " Received a Join Request. Adding to clusterMembers\n";
				clusterMembers.push_back(atoi(joinPacket->getSource()));
				priorityLevelsVector.push_back(currentPriorityLevel);
			}
	 		break;
		}
		case LEACH_ROUTING_TDMA_PACKET:{
			VirtualRingRoutingTDMAPacket *tdmaPacket = dynamic_cast <VirtualRingRoutingTDMAPacket*>(netPacket);
			if(!isCH && !isSink)
			{
				// clusterLength = tdmaPacket->getScheduleArraySize();
				// trace() << "Node " << self << ", my clusterLength variable changed, in received TDMA_PACKET, new one: " << clusterLength;
				for(int i=0; i<tdmaPacket->getScheduleArraySize(); i++) {
					if (tdmaPacket->getSchedule(i)==atoi(SELF_NETWORK_ADDRESS)) {	
						clusterLength = tdmaPacket->getScheduleArraySize();
						//trace() << "Node " << self << ", my clusterLength variable changed, in received TDMA_PACKET, new one: " << clusterLength;
						setStateSleep();						
						//trace() << "Node " << self << " Received TDMA_PACKET --> GOING TO SLEEP";
						if (getTimer(START_SLOT) == -1) {	// No hay un timer ya establecido
							setTimer(START_SLOT, i*slotLength);
						}
						//trace() << "Node " << self << " Received TDMA pkt, I am: "<< i << "th \n";
						// XXX-albarc De quien viene
						string source = tdmaPacket->getSource();
						trace() << "Node " << self << " Received TDMA pkt from " << source
								<< ", I am: "<< i << "th";
						mySlotsVector.push_back(i);
						//break;
					}
				}
			}
			break;
		}
	}
}

void VirtualRingRouting::timerFiredCallback(int index)
{
	switch (index) {
		/*
		case HELLO_WORLD:{	
			// Sink node send hello word to nodes in order to start the discory round
					
			VirtualRingRoutingPacket *helloPkt = new VirtualRingRoutingPacket("Hello Word Packet, I'm the sink node", NETWORK_LAYER_PACKET);
			
			helloPkt->setByteLength(advPacketSize);
			helloPkt->setVirtualRingRoutingPacketKind(HELLO_WORLD);
			helloPkt->setSource(SELF_NETWORK_ADDRESS);
			helloPkt->setDestination(BROADCAST_NETWORK_ADDRESS);
			toMacLayer(helloPkt, BROADCAST_MAC_ADDRESS);
			
			//setTimer(HELLO_WORLD, 2.0);
			if (getTimer(HELLO_WORLD) != 0) {
					cancelTimer(HELLO_WORLD);
			}	
			break;
		}
		*/
		case DISCOVERY_ROUND:{	
			// Broadcasts hello_world packet
			trace() << "---- The discovery Start ----";
			// stringClusterHeadSet.clear();
			// stringMemberFollowers.clear();
			// ringMembers.clear();
			VirtualRingRoutingDscvPacket *brdcstPkt = new VirtualRingRoutingDscvPacket("Broadcast initialisation Packet", NETWORK_LAYER_PACKET);
			brdcstPkt->setByteLength(advPacketSize);
			brdcstPkt->setVirtualRingRoutingPacketKind(BROADCAST_PACKET);
			brdcstPkt->setSource(SELF_NETWORK_ADDRESS);
			brdcstPkt->setDestination(BROADCAST_NETWORK_ADDRESS);
			brdcstPkt->setResidual(resourceModule->getRemainingEnergy()); // Residual energy of the node (Must be ok)
			brdcstPkt->setLocation(0,varX); // X Location of the node
			brdcstPkt->setLocation(1,varY); // Y Location of the node 			
			brdcstPkt->setLocation(2,uniform(0.0, 0.40)); // Location of the node (burial depth) randomly between the ground surface and 40cm depth
			
			//brdcstPkt->setLocation(uniform(0.0, 0.40)); // Location of the node (burial depth) randomly between the ground surface and 40cm depth
			toMacLayer(brdcstPkt, BROADCAST_MAC_ADDRESS);
			trace() << "Node " << self << " sends the broadcast packet for the neighbor discovery ";
			trace () << "Node : " << self << " Current round " << roundNumber;
			
			if (getTimer(DISCOVERY_ROUND) != 0) {
					cancelTimer(DISCOVERY_ROUND);
			}
			break;
		}	
		
		/*
		case DISCOVERY_ROUND:{
			trace() << "DISCOVERY_ROUND: CASE";
			setStateRx();
			setPowerLevel(maxPower);
			endFormClus = false;
			CHcandidates.clear();
			clusterMembers.clear();
			priorityLevelsVector.clear();
			TDMATable.clear();	// XXX-albarc 3/11/17 Error en simulaciones largas
			if (getTimer(START_SLOT) != 0) { 
				cancelTimer(START_SLOT);
			}
			
			if (roundNumber >= 1/percentage) {
				roundNumber=0;
				isCt = false;
				isCH = false;
			}

			//trace() << "#### Starting round number " << roundNumber << " ####";

			double randomNumber = uniform(0,1);
			double timer = uniform(0,1);

			if(isCH) {
				isCH = false;
				isCt = true;
			}
			if(isCt) {
				probability = 0;
			} else {
				if (roundNumber >= (1/percentage - 1)){
					probability = 1;
				}else {
					probability = percentage/(1-percentage*(roundNumber % (int) (1/percentage)));
				}
			}
			if (randomNumber<probability)
			{
				setTimer(SEND_ADV, (timer));
				setTimer(MAKE_TDMA, 2.0+timer);
				isCH=true;
			}
			if (!isCH) setTimer(JOIN_CH, (1.0+timer));
			if (isCH) {
				trace() << "## ROUND " << roundNumber << " : Node " << self << " is Cluster Head. ##";
			}
			roundNumber++;

			// XXX-albarc
			slot = 0;
			mySlotsVector.clear();

			setTimer(DISCOVERY_ROUND, roundLength);
			break;
		}
		*/
		case SEND_ADV:{	
			trace() << "SEND_ADV: CASE";
			VirtualRingRoutingPacket *crtlPkt = new VirtualRingRoutingPacket("ClusterHead Announcement Packet", NETWORK_LAYER_PACKET);
			crtlPkt->setByteLength(advPacketSize);
			crtlPkt->setVirtualRingRoutingPacketKind(LEACH_ROUTING_ADV_PACKET);
			crtlPkt->setSource(SELF_NETWORK_ADDRESS);
			crtlPkt->setDestination(BROADCAST_NETWORK_ADDRESS);
			toMacLayer(crtlPkt, BROADCAST_MAC_ADDRESS);
			//trace() << "Node " << self << " Sent Beacon";
			break;
		}
		case JOIN_CH:{
			trace() << "JOIN_CH: CASE, CHcandidates size: " << CHcandidates.size();
			if(CHcandidates.size()!=0){
				CHcandidates.sort(cmpRingRssi);
				VirtualRingRoutingJoinPacket *crtlPkt = new VirtualRingRoutingJoinPacket("ClusterMember Join Packet", NETWORK_LAYER_PACKET);
				crtlPkt->setVirtualRingRoutingPacketKind(LEACH_ROUTING_JOIN_PACKET);
				crtlPkt->setByteLength(joinPacketSize);	
				crtlPkt->setSource(SELF_NETWORK_ADDRESS);
				CHInfo info = *CHcandidates.begin();
				stringstream buffer;
				buffer << info.src;
				string dst = buffer.str();
				crtlPkt->setDestination(dst.c_str());

				// XXX-albarc Prioridad dentro del paquete de JOIN
				crtlPkt->setPriorityLevel(myPriorityLevel);

				toMacLayer(crtlPkt, BROADCAST_MAC_ADDRESS);
				endFormClus = true;
				//trace() << "Node " << self << " Sent Join Request to " << dst;
			}
			break;
		}
		case MAKE_TDMA:{
			trace() << "MAKE_TDMA: CASE, clusterMembers size: " << clusterMembers.size();
			if (clusterMembers.size()!=0){
				VirtualRingRoutingTDMAPacket *ctrlPkt = new VirtualRingRoutingTDMAPacket("ClusterHead TDMA Packet", NETWORK_LAYER_PACKET);
				ctrlPkt->setVirtualRingRoutingPacketKind(LEACH_ROUTING_TDMA_PACKET);
				ctrlPkt->setSource(SELF_NETWORK_ADDRESS);
				ctrlPkt->setDestination(BROADCAST_NETWORK_ADDRESS);
				clusterLength = clusterMembers.size();
				//trace() << "Node " << self << ", my clusterLength variable changed, in CASE MAKE_TDMA, new one: " << clusterLength;

				// XXX-albarc 18/07/17 En el paquete de JOIN está el nivel de prioridad
				int TDMATableSize = populateTDMATable();

				// Incorporar la tabla TDMA formada en el paquete TDMA a distribuir entre los cluster members
				ctrlPkt->setScheduleArraySize(TDMATableSize);
				for (std::vector<int>::const_iterator i = TDMATable.begin(); i != TDMATable.end(); ++i) {
					int pos = i - TDMATable.begin();
					ctrlPkt->setSchedule(pos, TDMATable[pos]);
				}

				// Imprimir la tabla TDMA como queda finalmente
				sizeSchedule = ctrlPkt->getScheduleArraySize();
				for(int i=0; i<sizeSchedule; i++) {
					trace() << "SCHEDULE, i = " << i << ", getSchedule[i] = " << ctrlPkt->getSchedule(i);
				}

				// Actualizar el tamaño del paquete de TDMA para que sea realista
				// dataPacketSize es el valor cuando está vacío: type + src + dest. Entendiendo que cada miembro del TDMA se codifica con un byte
				ctrlPkt->setByteLength(dataPacketSize + sizeSchedule);

				toMacLayer(ctrlPkt, BROADCAST_MAC_ADDRESS);
				//trace() << "Node " << self << " Sent TDMA pkt";
				setTimer(START_SLOT, sizeSchedule*slotLength);
			}
			else setTimer(START_SLOT, slotLength);
			break;
		}
		case START_SLOT:{
			trace() << "START_SLOT: CASE";
			miniSlot = 0;
			traceAlbarc() << "START SLOT number: " << slot;
			for (std::vector<int>::const_iterator i = mySlotsVector.begin(); i != mySlotsVector.end(); ++i) {
				int pos = i - mySlotsVector.begin();
				traceAlbarc() << "MY SLOTS VECTOR: " << mySlotsVector[pos];
			}
			if (isCH && clusterMembers.size()==0) {
				setTimer(START_SLOT, slotLength);
			} else {
				if (isCH && (sizeSchedule != 0)) {
					setTimer(START_SLOT, sizeSchedule*slotLength);
					//trace() << "Fired START_SLOT para el sendAggregate con sizeSchedule: " << sizeSchedule; 
					//trace() << "isCh? " << isCH << ", clusterLength = " << clusterLength;
				} else {
					if (mySlotsVector.size() > 1) {	// XXX-albarc Hay extra slots
						int distance = distanceToNextSlot();
						traceAlbarc() << "Distance to next slot " << distance;
						setTimer(START_SLOT,distance*slotLength);
					} else {
						setTimer(START_SLOT, clusterLength*slotLength);
					}					
					//trace() << "Fired START_SLOT de no CH con sizeSchedule: " << sizeSchedule; 
					//trace() << "isCh? " << isCH << ", clusterLength = " << clusterLength;
				}
			}
			if (isCH) {
				sendAggregate(); 
				if (delayBetweenPacketsEnabled && (delayBetweenPackets != 0)) {
					processBufferedPacketWithoutSending();
					setTimer(DELAY_BETWEEN_PACKETS, delayBetweenPackets);
					//trace() << "Node " << self << " Sent Pkt Aggr"  << "\n";
				} else {
					processBufferedPacket();
				}
			}
			if (!isCH){
				CHInfo info = *CHcandidates.begin();
				int power = maxPower - ((info.rssi)-(sensibility));
				levelTxPower(power);
				trace() << "Node " << self << ". MI SLOT. Sent Data Packet";
				if (delayBetweenPacketsEnabled && (delayBetweenPackets != 0)) {
					processBufferedPacketWithoutSending();
					setTimer(DELAY_BETWEEN_PACKETS, delayBetweenPackets);
				} else {
					processBufferedPacket();
				}
				setTimer(END_SLOT, slotLength);			
			}

			break;
		}
		case END_SLOT:
		{
			trace() << "END_SLOT: CASE --> Node " << self << " GOING TO SLEEP";
			if(totalPacketsBuffered > 0) {
				trace() << "FAILURE IS INDEED AN OPTION, quedan " << totalPacketsBuffered << " por mandar";
			}
			if (getTimer(DELAY_BETWEEN_PACKETS) != 0) { 
				cancelTimer(DELAY_BETWEEN_PACKETS);
			}
			//trace() << "Node " << self << " Sleept"  << "\n";
			if (!isSink && !isCH) setStateSleep();
			break;
		}
		// XXX-albarc
		case DELAY_BETWEEN_PACKETS:
		{
			//trace() << "DELAY_BETWEEN_PACKETS: CASE";
			sendSinglePacket();
			setTimer(DELAY_BETWEEN_PACKETS, delayBetweenPackets);
			miniSlot++;
			break;
		}

		case COUNTER_ENERGY_MONITORING:
		{
			energyConsumedInTimeBucket = resourceModule->getSpentEnergy();
			std::string s = std::to_string(currentTimeBucket);
			collectOutput("[LEACH] Energy consumption per bucket of node 43", s.c_str(), energyConsumedInTimeBucket);
			trace() << "Spent energy so far: " << energyConsumedInTimeBucket;
			currentTimeBucket++;
			setTimer(COUNTER_ENERGY_MONITORING, timeBucketDuration);
			break;
		}
	}
}

void VirtualRingRouting::sendAggregate()
{
	if(bufferAggregate.size()!=0)
	{	
		double bitsLength = bufferAggregate.size() * dataPacketSize * 1000;
		double energyBit = (aggrConsumption / pow(10,9)) * bitsLength;
		powerDrawn(energyBit);
		VirtualRingRoutingDataAggregatedPacket *aggrPacket = new VirtualRingRoutingDataAggregatedPacket("ClusterHead Aggregated Packet", NETWORK_LAYER_PACKET);

		int numPacks = bufferAggregate.size();

		// XXX-albarc Rellenar los arrays de sources, seqNum y timestamp.
		RoutingPacket netPacket;	// En bufferAggregate están los RoutingPackets que han ido llegando de los clusterMembers y del propio CH
		ApplicationPacket *appPacket;	// Los RoutingPackets encapsulan un ApplicationPacket en el que está el timestamp de creación
		const char *indivSource;
		int seqNum;
		simtime_t creationTimestamp;

		aggrPacket->setIndivSourcesArraySize(numPacks);
		aggrPacket->setIndivSeqNumArraySize(numPacks);
		aggrPacket->setIndivCreationTimestampArraySize(numPacks);
		for (std::vector<RoutingPacket>::const_iterator i = bufferAggregate.begin(); i != bufferAggregate.end(); ++i) {
			int pos = i - bufferAggregate.begin();

			netPacket = bufferAggregate[pos];
			appPacket = check_and_cast <ApplicationPacket*>(netPacket.decapsulate());	// El timestamp es campo del paquete de aplicación, hay que desencapsular.

			indivSource = netPacket.getSource();
			seqNum = netPacket.getSequenceNumber();
			creationTimestamp = appPacket->getAppNetInfoExchange().timestamp;

			aggrPacket->setIndivSources(pos, atoi(indivSource));
			aggrPacket->setIndivSeqNum(pos, seqNum);
			aggrPacket->setIndivCreationTimestamp(pos, creationTimestamp);

			trace() << "CH " << self << ", AGREGANDO: Paquete #" <<  seqNum << ", de source " << indivSource << ", created at " << creationTimestamp;
		}

		aggrPacket->setByteLength(dataPacketSize + (numPacks * 7));	// Los 9 bytes del paquete mínimo, más 7 bytes por source (1 de la source, 2 del seqNum y 4 del timestamp).

		trace() << "Soy el CH " << self << ", sending aggregate packet of " << aggrPacket->getByteLength() <<
			" bytes, formado por " << numPacks << " paquetes";

		aggrPacket->setVirtualRingRoutingPacketKind(LEACH_ROUTING_DATA_AGGREGATED_PACKET);
		aggrPacket->setSource(SELF_NETWORK_ADDRESS);
		aggrPacket->setDestination(SINK_NETWORK_ADDRESS);

		bufferPacket(aggrPacket);
		bufferAggregate.clear();
	}
}

void VirtualRingRouting::processBufferedPacket()
{
	totalPacketsBuffered = tempTXBuffer.size() + TXBuffer.size();
	trace() << "En processBufferedPacket, tengo " << tempTXBuffer.size() << " paquetes en tempTXBuffer y "
		<< TXBuffer.size() << " en TXBuffer, en total " << totalPacketsBuffered;
	while (!tempTXBuffer.empty())
	{
		cPacket *pkt = tempTXBuffer.front();	
		VirtualRingRoutingPacket *netPacket = dynamic_cast <VirtualRingRoutingPacket*>(pkt);
		CHInfo info = *CHcandidates.begin();
		stringstream buffer;
		buffer << info.src;
		string dst = buffer.str();
		netPacket->setDestination(dst.c_str());
		bufferPacket(netPacket);
		tempTXBuffer.pop();
	}

	while (!TXBuffer.empty()) 
	{
		cPacket *pkt = TXBuffer.front();
		VirtualRingRoutingPacket *myPacket = dynamic_cast <VirtualRingRoutingPacket*>(pkt);
		toMacLayer(pkt, BROADCAST_MAC_ADDRESS);
		
		collectOutput("[LEACH] Individual packets sent", SELF_NETWORK_ADDRESS);

		TXBuffer.pop();

		if (totalPacketsBuffered > 0) {
			totalPacketsBuffered--;
		}

		// XXX-albarc Para ver cual es el numero de paquete
		trace() << "Nodo " << self << ", toMacLayer el paquete con seqNum " << myPacket->getSequenceNumber();		
	}
}

void VirtualRingRouting::processBufferedPacketWithoutSending()
{
	totalPacketsBuffered = tempTXBuffer.size() + TXBuffer.size();
	trace() << "En processBufferedPacketWithoutSending, tengo " << tempTXBuffer.size() << " paquetes en tempTXBuffer y "
		<< TXBuffer.size() << " en TXBuffer, en total " << totalPacketsBuffered;
	while (!tempTXBuffer.empty())
	{
		cPacket *pkt = tempTXBuffer.front();	
		VirtualRingRoutingPacket *netPacket = dynamic_cast <VirtualRingRoutingPacket*>(pkt);
		CHInfo info = *CHcandidates.begin();
		stringstream buffer;
		buffer << info.src;
		string dst = buffer.str();
		netPacket->setDestination(dst.c_str());
		bufferPacket(netPacket);
		tempTXBuffer.pop();
	}
}

void VirtualRingRouting::sendSinglePacket()
{	
	if (!TXBuffer.empty()) {
		cPacket *pkt = TXBuffer.front();
		VirtualRingRoutingPacket *myPacket = dynamic_cast <VirtualRingRoutingPacket*>(pkt);
		toMacLayer(pkt, BROADCAST_MAC_ADDRESS);

		collectOutput("[LEACH] Individual packets sent", SELF_NETWORK_ADDRESS);

		TXBuffer.pop();

		if (totalPacketsBuffered > 0) {
			totalPacketsBuffered--;
		}

		// XXX-albarc Porque en este punto el slot ya ha sido incrementado para la siguiente
		int slot_actual = (slot - 1);
		if (slot_actual == -1) {
			slot_actual = mySlotsVector.size() - 1;
		}

		// XXX-albarc Para ver cual es el numero de paquete
		trace() << "Nodo " << self << ", toMacLayer el paquete con seqNum " << myPacket->getSequenceNumber()
			<< " en el slot " << slot_actual << " y en el minislot " << miniSlot
			<< ", quedan buffereados: " << totalPacketsBuffered;
	}

}

void VirtualRingRouting::setStateRx()
{
	send(createRadioCommand(SET_STATE, RX), "toMacModule");	
}

void VirtualRingRouting::setPowerLevel(double powerLevel)
{
	send(createRadioCommand(SET_TX_OUTPUT, powerLevel), "toMacModule");
}

void VirtualRingRouting::setStateSleep()
{
	send(createRadioCommand(SET_STATE, SLEEP), "toMacModule");
}

void VirtualRingRouting::levelTxPower(int linkBudget)
{
	vector<int>::iterator constIterator;
	for (constIterator = powers.begin();
		constIterator != powers.end();
	        constIterator++ ) {
		if(*constIterator > (linkBudget))
		{
			setPowerLevel(*constIterator);
			break;
		}
	}
}

void VirtualRingRouting::readXMLparams()
{
	cXMLElement *rootelement = par("powersConfig").xmlValue();
	if (!rootelement) endSimulation();
	cXMLElement* data = rootelement->getFirstChildWithTag("maxPower");
	maxPower = atoi(data->getNodeValue());
	data = rootelement->getFirstChildWithTag("sensibility");
	sensibility = atoi(data->getNodeValue());
	data = rootelement->getFirstChildWithTag("aggrConsumption");
	aggrConsumption = atoi(data->getNodeValue());
	cXMLElementList sources = rootelement->getChildrenByTagName("power");
	for (int s = 0; s < sources.size(); s++)
		powers.push_back(atoi(sources[s]->getNodeValue()));
	if (powers.size() < 1) endSimulation();
	sort(powers.begin(), powers.end());
}

bool cmpRingRssi(CHInfo a, CHInfo b){
	return (a.rssi > b.rssi);
}

void VirtualRingRouting::finishSpecific() {
	// Solo se guardan del sink, porque como CastaliaResults saca la media por defecto
	// lo dividiría entre el número de nodos y se falsearía el resultado. De esta forma
	// cada output solo tiene una entrada por lo que sale lo mismo poniendo o no la opción
	// --sum (que es lo que haría sacar el acumulado en vez de la media)
	if (isSink) {
		int numNodesNoSink = numNodes - 1;
		// int numPriorityNodes = prioritySourcesVector.size();
		int numPriorityLevel_1_Nodes = priorityLevel_1_SourcesVector.size();
		int numPriorityLevel_2_Nodes = priorityLevel_2_SourcesVector.size();
		int numRegularNodes = numNodesNoSink - numPriorityLevel_1_Nodes - numPriorityLevel_2_Nodes;
		/* trace() << "[LEACH] Hay un total de " << numNodesNoSink << " nodos sin contar al sink, de los que " << numPriorityLevel_1_Nodes
			<< " son de priority level 1, " << numPriorityLevel_2_Nodes << " son de priority level 2 y " << numRegularNodes << " son regulares."; */

		// Media de paquetes recibidos en el sink
		if (numNodesNoSink > 0) {	
			declareOutput("[LEACH] Average packets received at the sink");
			collectOutput("[LEACH] Average packets received at the sink", "", totalPacketsReceived/numNodesNoSink);

			declareOutput("[LEACH] Average latency of all packets, regardless of priority, in s");
			collectOutput("[LEACH] Average latency of all packets, regardless of priority, in s", "", totalLatencyOfAllPackets/totalPacketsReceived);
		}
		totalPacketsReceived = 0;
		totalLatencyOfAllPackets = 0;

		// Total de paquetes de priority level 1 recibidos en el sink
		if (numPriorityLevel_1_Nodes > 0) {
			declareOutput("[LEACH] Average priority level 1 packets received at the sink");
			collectOutput("[LEACH] Average priority level 1 packets received at the sink", "", totalPriorityLevel_1_PacketsReceived/numPriorityLevel_1_Nodes);

			declareOutput("[LEACH] Average latency of priority level 1 packets, in s");
			collectOutput("[LEACH] Average latency of priority level 1 packets, in s", "", totalLatencyOfPL1Packets/totalPriorityLevel_1_PacketsReceived);
		}
		totalPriorityLevel_1_PacketsReceived = 0;
		totalLatencyOfPL1Packets = 0;

		// Total de paquetes de priority level 2 recibidos en el sink
		if (numPriorityLevel_2_Nodes > 0) {
			declareOutput("[LEACH] Average priority level 2 packets received at the sink");
			collectOutput("[LEACH] Average priority level 2 packets received at the sink", "", totalPriorityLevel_2_PacketsReceived/numPriorityLevel_2_Nodes);

			declareOutput("[LEACH] Average latency of priority level 2 packets, in s");
			collectOutput("[LEACH] Average latency of priority level 2 packets, in s", "", totalLatencyOfPL2Packets/totalPriorityLevel_2_PacketsReceived);
		}
		totalPriorityLevel_2_PacketsReceived = 0;
		totalLatencyOfPL2Packets = 0;

		// Total de paquetes regulares recibidos en el sink
		if (numRegularNodes > 0) {
			declareOutput("[LEACH] Average regular packets received at the sink");
			collectOutput("[LEACH] Average regular packets received at the sink", "", totalRegularPacketsReceived/numRegularNodes);

			declareOutput("[LEACH] Average latency of regular packets, in s");
			collectOutput("[LEACH] Average latency of regular packets, in s", "", totalLatencyOfRegularPackets/totalRegularPacketsReceived);
		}
		totalRegularPacketsReceived = 0;
		totalLatencyOfRegularPackets = 0;

		// Nodo 43
		declareOutput("[LEACH] Average latency of node 43, in s");
		collectOutput("[LEACH] Average latency of node 43, in s", "", totalLatencyOfNode43Packets/totalNode43PacketsReceived);
		totalLatencyOfNode43Packets = 0;
		totalNode43PacketsReceived = 0;
	}
}

bool VirtualRingRouting::isPriorityLevelSource(int src, int level){
	bool result = false;
	if (level == 1) {
		for (std::vector<int>::const_iterator i = priorityLevel_1_SourcesVector.begin(); i != priorityLevel_1_SourcesVector.end(); ++i) {
			int pos = i - priorityLevel_1_SourcesVector.begin();
			int currentSource = priorityLevel_1_SourcesVector[pos];
			if (src == currentSource) {
				result = true;
				break;
			}
		}
	} else if (level == 2) {
		for (std::vector<int>::const_iterator i = priorityLevel_2_SourcesVector.begin(); i != priorityLevel_2_SourcesVector.end(); ++i) {
			int pos = i - priorityLevel_2_SourcesVector.begin();
			int currentSource = priorityLevel_2_SourcesVector[pos];
			if (src == currentSource) {
				result = true;
				break;
			}
		}
	} else {
		result = false;
	}
	return result;
}

int VirtualRingRouting::distanceToNextSlot(){
	int distanceToNextSlot = 0;
	if ((slot + 2) <= mySlotsVector.size()) {	// No es el último
		distanceToNextSlot = mySlotsVector[slot + 1] - mySlotsVector[slot];		
		slot++;
	} else {
		distanceToNextSlot = clusterLength - mySlotsVector[slot];	// Los slots que quedan hasta el final del frame
		distanceToNextSlot += mySlotsVector[0];	// Los slots que hay desde el principio del frame hasta el primero
		slot = 0;
	}

	return distanceToNextSlot;
}

int VirtualRingRouting::populateTDMATable(){
	int tableSize = 0;

	int numMembersPriority_1 = 0, numMembersPriority_2 = 0, numMembersPriority_3 = 0;

	int numExtraSlots_priorityLevel_1 = std::round(clusterMembers.size() * slotsIncreasePercentagePriorityLevel_1);
	int numExtraSlots_priorityLevel_2 = std::round(clusterMembers.size() * slotsIncreasePercentagePriorityLevel_2);
	
	// Rellenar la tabla TDMA en el orden en el que aparecen en el clusterMembers
	for (std::vector<int>::const_iterator i = clusterMembers.begin(); i != clusterMembers.end(); ++i) {
		int pos = i - clusterMembers.begin();
		switch(priorityLevelsVector[pos]) {
			case 1:
				for (int j = 0; j < numExtraSlots_priorityLevel_1 + 1; j++) {
					TDMATable.push_back(clusterMembers[pos]);
				}
				numMembersPriority_1++;
				break;

			case 2:
				for (int j = 0; j < numExtraSlots_priorityLevel_2 + 1; j++) {
					TDMATable.push_back(clusterMembers[pos]);
				}
				numMembersPriority_2++;
				break;

			case 3:
			default:
				TDMATable.push_back(clusterMembers[pos]);
				numMembersPriority_3++;
				break;
		}
		
	}

	// Devolver el tamaño de la tabla TDMA
	tableSize = TDMATable.size();
	trace() << "populateTDMATable(), TDMATable size: " << TDMATable.size() << "; priority_1: " << numMembersPriority_1 << " members, " 
		<< numExtraSlots_priorityLevel_1 << " extra slots each; priority_2: " << numMembersPriority_2 << " members, " 
		<< numExtraSlots_priorityLevel_2 << " extra slots each; priority_3: " << numMembersPriority_3 << " members";
	// for(int i=0; i<tableSize; i++) {
	// 	trace() << "TDMATable, i = " << i << ", TDMATable[i] = " << TDMATable[i];
	// }

	return tableSize;
}
