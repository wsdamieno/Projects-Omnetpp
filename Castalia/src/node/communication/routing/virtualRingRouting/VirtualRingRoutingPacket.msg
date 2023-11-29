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

cplusplus {{
#include "RoutingPacket_m.h"
}}

class RoutingPacket;


enum VirtualRingRoutingPacket_Type
{
	LEACH_ROUTING_ADV_PACKET 				= 1;		
	LEACH_ROUTING_JOIN_PACKET 				= 2;		
	LEACH_ROUTING_TDMA_PACKET 				= 3;		
	LEACH_ROUTING_DATA_PACKET 				= 4;		
	LEACH_ROUTING_DATA_SINGLE_PACKET 		= 5;		
	LEACH_ROUTING_DATA_AGGREGATED_PACKET 	= 6;
};

packet VirtualRingRoutingPacket extends RoutingPacket
{	
	int VirtualRingRoutingPacketKind enum (VirtualRingRoutingPacket_Type);
};

// XXX-albarc 15/06/18 - Different types of packets with different extra fields
packet VirtualRingRoutingJoinPacket extends VirtualRingRoutingPacket
{
	int priorityLevel;
}

packet VirtualRingRoutingTDMAPacket extends VirtualRingRoutingPacket
{
	int schedule[];
}

packet VirtualRingRoutingDataAggregatedPacket extends VirtualRingRoutingPacket
{
	// Sources, seqNum y timestamp de los paquetes individuales agregados
	int indivSources[];
	int indivSeqNum[];
	simtime_t indivCreationTimestamp[];
}