//
// Copyright (C) OpenSim Ltd.
//
// This program is free software; you can redistribute it and/or
// modify it under the terms of the GNU Lesser General Public License
// as published by the Free Software Foundation; either version 2
// of the License, or (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU Lesser General Public License for more details.
//
// You should have received a copy of the GNU Lesser General Public License
// along with this program; if not, see http://www.gnu.org/licenses/.
//

#include "inet/common/ModuleAccess.h"
#include "inet/queueing/common/PacketDelayer.h"

namespace inet {
namespace queueing {

Define_Module(PacketDelayer);

void PacketDelayer::handleMessage(cMessage *message)
{
    if (message->isSelfMessage()) {
        auto packet = check_and_cast<Packet *>(message);
        pushOrSendPacket(packet, outputGate, consumer);
    }
    else
        throw cRuntimeError("Unknown message");
}

void PacketDelayer::pushPacket(Packet *packet, cGate *gate)
{
    Enter_Method("pushPacket");
    take(packet);
    EV_INFO << "Delaying packet " << packet->getName() << "." << endl;
    scheduleAt(simTime() + par("delay"), packet);
    numProcessedPackets++;
    processedTotalLength += packet->getTotalLength();
    updateDisplayString();
}

void PacketDelayer::handleCanPushPacket(cGate *gate)
{
    Enter_Method("handleCanPushPacket");
    if (producer != nullptr)
        producer->handleCanPushPacket(inputGate->getPathStartGate());
}

void PacketDelayer::handlePushPacketProcessed(Packet *packet, cGate *gate, bool successful)
{
    Enter_Method("handlePushPacketProcessed");
    producer->handlePushPacketProcessed(packet, gate, successful);
}

} // namespace queueing
} // namespace inet

