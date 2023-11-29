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

#ifndef _VIRTUALRINGROUTING_H_
#define _VIRTUALRINGROUTING_H_

#include <queue>
#include <vector>
#include <omnetpp.h>
#include <algorithm>
#include <string>
#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <sstream>
#include "VirtualRouting.h"
#include "VirtualApplication.h"	
#include "VirtualRingRoutingPacket_m.h"
#include "ApplicationPacket_m.h"
#include "NoMobilityManager.h"


using namespace std;

enum VirtualRingRoutingTimers {
	START_ROUND = 1,	
	SEND_ADV = 2,	
	JOIN_CH = 3,		
	MAKE_TDMA = 4,			
	START_SLOT = 5,	
	END_SLOT = 6,
	DELAY_BETWEEN_PACKETS = 7,	// XXX-albarc
	COUNTER_ENERGY_MONITORING = 8,	// XXX-albarc
};

struct CHInfo
{
	int src;
	double rssi;
};

class VirtualRingRouting : public VirtualRouting {

private:
	
	string applicationID;
	int advPacketSize;
	int tdmaPacketSize;
	int dataPacketSize;
	int joinPacketSize;

	double maxPower;
	double sensibility;
	double aggrConsumption;
	
	double slotLength;
	int clusterLength;
	double percentage;
	double probability;
	double roundLength;
	int roundNumber;
	int dataSN;
	
	bool isCH;
	bool isSink;
	bool isCt;
	bool endFormClus;

	vector<RoutingPacket> bufferAggregate;
	vector<int> powers;
	queue <cPacket *> tempTXBuffer;
	vector <int> clusterMembers;
	list <CHInfo> CHcandidates;

	/* XXX-albarc Añadir slots extra para sources prioritarias */
	int sizeSchedule;

	/* XXX-albarc 18/07/17 Slots extra determinados por el campo de nivel de prioridad en el paquete de JOIN */
	double slotsIncreasePercentagePriorityLevel_1;
	double slotsIncreasePercentagePriorityLevel_2;
	vector<int> priorityLevelsVector; // Se rellenará por los CH al ir recibiendo mensajes de JOIN
	vector<int> TDMATable; // Se rellenará por los CH teniendo en cuenta los clusterMembers y sus diferentes niveles de prioridad
	int myPriorityLevel; // El propio de cada nodo, que incorporará en sus paquetes de JOIN

	// Para los collectOutput, ya que el sink donde se desagregan no tiene la información de los paquetes de JOIN
	const char *priorityLevel_1_Sources;
	vector<int> priorityLevel_1_SourcesVector;
	const char *priorityLevel_2_Sources;
	vector<int> priorityLevel_2_SourcesVector;
	int totalPriorityLevel_1_PacketsReceived;
	int totalPriorityLevel_2_PacketsReceived;

	// XXX-albarc Para no mandar todos los paquetes en el mismo momento y evitar colisiones
	bool delayBetweenPacketsEnabled;
	double delayBetweenPackets;

	// XXX-albarc Para calcular las medias de recibidos al final
	int totalPacketsReceived;
	int totalRegularPacketsReceived;
	int numNodes;

	// XXX-albarc Para calcular la latencia según prioridad
	double totalLatencyOfAllPackets;
	double totalLatencyOfPL1Packets;
	double totalLatencyOfPL2Packets;
	double totalLatencyOfRegularPackets;

	double totalLatencyOfNode43Packets;
	double totalNode43PacketsReceived;

	// Histograma de paquetes recibidos por buckets de tiempo
	int simTimeLimit;
	int numTimeBuckets;
	int timeBucketDuration;
	double energyConsumedInTimeBucket;
	int currentTimeBucket;
	ResourceManager* resourceModule;

	// PRUEBA CALCULAR MINISLOTS
	int slot;
	int miniSlot;
	int totalPacketsBuffered;
	vector<int> mySlotsVector;

protected:

	void startup();
	void fromApplicationLayer(cPacket *, const char *);
	void fromMacLayer(cPacket *, int, double, double);
	void timerFiredCallback(int);
	void processBufferedPacket();
	
	void sendAggregate();
	void setPowerLevel(double);
	void setStateSleep();
	void setStateRx();
	void levelTxPower(int);	
	void readXMLparams();
	
	void processBufferedPacketWithoutSending();	// XXX-albarc	
	void sendSinglePacket();	// XXX-albarc

	void finishSpecific();	// XXX-albarc
	int distanceToNextSlot();	// XXX-albarc

	int populateTDMATable();	// XXX-albarc
	bool isPriorityLevelSource(int, int);	// XXX-albarc

};
bool cmpRingRssi(CHInfo a, CHInfo b);

#endif			
