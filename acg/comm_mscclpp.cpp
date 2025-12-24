/* This file is part of acg.
 *
 * Copyright 2025 Koç University and Simula Research Laboratory
 *
 * MSCCLPP C++ wrapper implementation
 */

#ifdef ACG_HAVE_MSCCLPP

#include "acg/config.h"
#include "acg/error.h"
#include "acg/comm.h"

#include <mscclpp/core.hpp>
#include <mscclpp/communicator.hpp>
#include <memory>
#include <stdexcept>

extern "C" {

/* Internal structure to hold MSCCLPP communicator data */
struct mscclpp_comm_opaque {
    std::shared_ptr<mscclpp::Communicator> comm;
    int rank;
    int size;
};

/**
 * 'acgcomm_mscclpp_create()' creates a new MSCCLPP communicator.
 * This function should be called by the application to initialize MSCCLPP.
 */
int acgcomm_mscclpp_create(
    mscclpp_comm_t* mscclpp_comm,
    int rank,
    int size,
    const char* bootstrap_server,
    int* errcode)
{
    try {
        auto* comm_data = new mscclpp_comm_opaque;
        
        // Create bootstrap communicator
        // Note: Actual bootstrap method depends on your setup
        // This is a simplified example using TCP bootstrap
        auto bootstrap = std::make_shared<mscclpp::TcpBootstrap>(rank, size);
        
        // Initialize MSCCLPP communicator
        comm_data->comm = std::make_shared<mscclpp::Communicator>(bootstrap);
        comm_data->rank = rank;
        comm_data->size = size;
        
        *mscclpp_comm = comm_data;
        return ACG_SUCCESS;
        
    } catch (const std::exception& e) {
        fprintf(stderr, "MSCCLPP create error: %s\n", e.what());
        if (errcode) *errcode = -1;
        return ACG_ERR_MSCCLPP;
    }
}

/**
 * 'acgcomm_mscclpp_destroy()' destroys a MSCCLPP communicator.
 */
void acgcomm_mscclpp_destroy(mscclpp_comm_t mscclpp_comm)
{
    if (mscclpp_comm) {
        delete static_cast<mscclpp_comm_opaque*>(mscclpp_comm);
    }
}

/**
 * 'acgcomm_mscclpp_get_size()' returns the size of the communicator.
 */
int acgcomm_mscclpp_get_size(
    mscclpp_comm_t mscclpp_comm,
    int* size)
{
    if (!mscclpp_comm) return ACG_ERR_INVALID_VALUE;
    
    auto* comm_data = static_cast<mscclpp_comm_opaque*>(mscclpp_comm);
    *size = comm_data->size;
    return ACG_SUCCESS;
}

/**
 * 'acgcomm_mscclpp_get_rank()' returns the rank of the current process.
 */
int acgcomm_mscclpp_get_rank(
    mscclpp_comm_t mscclpp_comm,
    int* rank)
{
    if (!mscclpp_comm) return ACG_ERR_INVALID_VALUE;
    
    auto* comm_data = static_cast<mscclpp_comm_opaque*>(mscclpp_comm);
    *rank = comm_data->rank;
    return ACG_SUCCESS;
}

/**
 * 'acgcomm_mscclpp_allreduce()' performs an all-reduce operation.
 * 
 * Note: MSCCLPP uses execution plans for collective operations.
 * This is a simplified implementation that would need to be expanded
 * with proper execution plan handling.
 */
int acgcomm_mscclpp_allreduce(
    mscclpp_comm_t mscclpp_comm,
    const void* sendbuf,
    void* recvbuf,
    size_t count,
    size_t datatype_size,
    cudaStream_t stream,
    int* errcode)
{
    if (!mscclpp_comm) return ACG_ERR_INVALID_VALUE;
    
    try {
        auto* comm_data = static_cast<mscclpp_comm_opaque*>(mscclpp_comm);
        
        // MSCCLPP requires execution plans for collectives
        // This is a placeholder - actual implementation would:
        // 1. Load or create an execution plan for allreduce
        // 2. Register memory buffers
        // 3. Execute the plan
        // 4. Handle stream synchronization
        
        // For now, return not implemented
        fprintf(stderr, "MSCCLPP allreduce: execution plan implementation needed\n");
        return ACG_ERR_MSCCLPP_NOT_SUPPORTED;
        
    } catch (const std::exception& e) {
        fprintf(stderr, "MSCCLPP allreduce error: %s\n", e.what());
        if (errcode) *errcode = -1;
        return ACG_ERR_MSCCLPP;
    }
}

/**
 * 'acgcomm_mscclpp_barrier()' performs a barrier operation.
 */
int acgcomm_mscclpp_barrier(
    mscclpp_comm_t mscclpp_comm,
    cudaStream_t stream,
    int* errcode)
{
    if (!mscclpp_comm) return ACG_ERR_INVALID_VALUE;
    
    try {
        // Simplified barrier - synchronize the CUDA stream
        // A proper implementation would use MSCCLPP's barrier primitive
        cudaError_t cuda_err = cudaStreamSynchronize(stream);
        if (cuda_err != cudaSuccess) {
            if (errcode) *errcode = cuda_err;
            return ACG_ERR_CUDA;
        }
        
        return ACG_SUCCESS;
        
    } catch (const std::exception& e) {
        fprintf(stderr, "MSCCLPP barrier error: %s\n", e.what());
        if (errcode) *errcode = -1;
        return ACG_ERR_MSCCLPP;
    }
}

} // extern "C"

#endif // ACG_HAVE_MSCCLPP