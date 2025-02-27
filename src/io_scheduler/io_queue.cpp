/*
 *   BSD LICENSE
 *   Copyright (c) 2021 Samsung Electronics Corporation
 *   All rights reserved.
 *
 *   Redistribution and use in source and binary forms, with or without
 *   modification, are permitted provided that the following conditions
 *   are met:
 *
 *     * Redistributions of source code must retain the above copyright
 *       notice, this list of conditions and the following disclaimer.
 *     * Redistributions in binary form must reproduce the above copyright
 *       notice, this list of conditions and the following disclaimer in
 *       the documentation and/or other materials provided with the
 *       distribution.
 *     * Neither the name of Samsung Electronics Corporation nor the names of
 *       its contributors may be used to endorse or promote products derived
 *       from this software without specific prior written permission.
 *
 *   THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 *   "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 *   LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 *   A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 *   OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 *   SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 *   LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 *   DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 *   THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 *   (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 *   OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#include "src/io_scheduler/io_queue.h"

#include <assert.h>

#include "Air.h"
#include "src/spdk_wrapper/event_framework_api.h"
#include "src/include/pos_event_id.hpp"
#include "src/bio/ubio.h"
#include "src/logger/logger.h"

namespace pos
{
IOQueue::IOQueue(void)
{
}

IOQueue::~IOQueue(void)
{
}

UbioSmartPtr
IOQueue::DequeueUbio(void)
{
    std::unique_lock<std::mutex> uniqueLock(queueLock);
    UbioSmartPtr ubio = nullptr;
    uint32_t qSize = queue.size();
    airlog("Q_IOQueue", "AIR_BASE", 0, qSize);
    if (false == queue.empty())
    {
        ubio = queue.front();
        assert(nullptr != ubio);
        queue.pop();
    }

    return ubio;
}

void
IOQueue::EnqueueUbio(UbioSmartPtr input)
{
    if (nullptr == input)
    {
        POS_TRACE_WARN(EID(IOQ_ENQUEUE_NULL_UBIO),
            "Enqueue null ubio");
        return;
    }

    std::unique_lock<std::mutex> uniqueLock(queueLock);
    queue.push(input);
}

int
IOQueue::GetQueueSize(void)
{
    return queue.size();
}

} // namespace pos
