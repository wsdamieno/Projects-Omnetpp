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

package node.communication.routing.leachRouting;

simple LeachRouting like node.communication.routing.iRouting
{
parameters:
	string applicationID = default ("leachTest");
	bool collectTraceInfo = default (false);	// XXX-albarc No tenía default y daba fallo en las simulaciones
	bool collectTraceInfoAlbarc = default (false);	// XXX-albarc
	int maxNetFrameSize = default (0);
	int netDataFrameOverhead = default (14);
	int netBufferSize = default (32);
	bool isSink = default (false);
	
	double percentage;	
	double roundLength @unit(s);	
	double slotLength;

	//routing layer packet sizes
	int advPacketSize = default (9); // Type + Source + Destination = 9 bytes
	int joinPacketSize = default (10);	// XXX-albarc Type + Source + Destination + priorityLevel = 10 bytes
	int tdmaPacketSize = default (150); // Type + Source + Destination + tdma = 150 bytes. No se usa, realmente se calcula en ejecucion con los miembros del cluster
	int dataPacketSize = default (9);	// Vacío de datos

	//Parameters used to power control.
	xml powersConfig;

	// XXX-albarc Slots extra en funcion del nivel de prioridad que se manda en el paquete de JOIN, en forma de porcentaje sobre el total de miembros del cluster
	int myPriorityLevel = default (3); // El priority level de cada nodo
	double slotsIncreasePercentagePriorityLevel_1 = default (0.15);
	double slotsIncreasePercentagePriorityLevel_2 = default (0.05);
	string priorityLevel_1_Sources  = default ("");
	string priorityLevel_2_Sources  = default ("");

	// XXX-albarc Para no mandar todos los paquetes en el mismo momento y evitar colisiones
	bool delayBetweenPacketsEnabled = default (false);
	double delayBetweenPackets = default (0.05);

	// XXX-albarc Buckets para el histograma de paquetes recibidos
	int numTimeBuckets = default (20);

gates: 
	output toCommunicationModule;
	output toMacModule;
	input fromCommunicationModule;
	input fromMacModule;
	input fromCommModuleResourceMgr;
}

