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

#pragma once

#include "src/helper/json/json_helper.h"
#include "src/logger/logger.h"
#include "src/include/grpc_server_socket_address.h"
#include "src/include/pos_event_id.h"
#include "src/volume/i_volume_event_manager.h"
#include "proto/generated/cpp/pos_rpc.grpc.pb.h"
#include "proto/generated/cpp/pos_rpc.pb.h"

#include <list>
#include <map>
#include <string>
#include <vector>
#include <nlohmann/json.hpp>
#include <grpc++/grpc++.h>

namespace pos
{
class GrpcVolumeManagement final : public pos_rpc::PosManagement::Service
{
public:
    GrpcVolumeManagement(void);
    ~GrpcVolumeManagement(void);

    void RunServer(std::string address);

    virtual ::grpc::Status CreateArray(
        ::grpc::ServerContext* context,
        const ::pos_rpc::CreateArrayRequest* request,
        ::pos_rpc::PosResponse* response) override;
    virtual ::grpc::Status DeleteArray(
        ::grpc::ServerContext* context,
        const ::pos_rpc::DeleteArrayRequest* request,
        ::pos_rpc::PosResponse* response) override;
    virtual ::grpc::Status CreateVolume(
        ::grpc::ServerContext* context,
        const ::pos_rpc::CreateVolumeRequest* request,
        ::pos_rpc::PosResponse* response) override;
    virtual ::grpc::Status DeleteVolume(
        ::grpc::ServerContext* context,
        const ::pos_rpc::DeleteVolumeRequest* request,
        ::pos_rpc::PosResponse* response) override;
    virtual ::grpc::Status MountVolume(
        ::grpc::ServerContext* context,
        const ::pos_rpc::MountVolumeRequest* request,
        ::pos_rpc::PosResponse* response) override;
    virtual ::grpc::Status UnmountVolume(
        ::grpc::ServerContext* context,
        const ::pos_rpc::UnmountVolumeRequest* request,
        ::pos_rpc::PosResponse* response) override;

    virtual ::grpc::Status UpdateVoluemMeta(
        ::grpc::ServerContext* context,
        const ::pos_rpc::UpdateVoluemMetaRequest* request,
        ::pos_rpc::PosResponse* response) override;
    virtual ::grpc::Status GetArrayList(
        ::grpc::ServerContext* context,
        const ::pos_rpc::GetArrayListRequest* request,
        ::pos_rpc::ArrayListResponse* response) override;
    virtual ::grpc::Status GetVolumeList(
        ::grpc::ServerContext* context,
        const ::pos_rpc::GetVolumeListRequest* request,
        ::pos_rpc::VolumeListResponse* response) override;
private:
    std::unique_ptr<::grpc::Server> posMgrGrpcServer;
};
}