/*
 * Copyright (C) 2011-2018 Intel Corporation. All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 *   * Redistributions of source code must retain the above copyright
 *     notice, this list of conditions and the following disclaimer.
 *   * Redistributions in binary form must reproduce the above copyright
 *     notice, this list of conditions and the following disclaimer in
 *     the documentation and/or other materials provided with the
 *     distribution.
 *   * Neither the name of Intel Corporation nor the names of its
 *     contributors may be used to endorse or promote products derived
 *     from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 * A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 * OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 */


// Enclave2.cpp : Defines the exported functions for the DLL application
#include "sgx_eid.h"
#include "Enclave2_t.h"
#include "EnclaveMessageExchange.h"
#include "error_codes.h"
#include "Utility_E2.h"
#include "sgx_thread.h"
#include "sgx_dh.h"
#include <map>

#define UNUSED(val) (void)(val)

std::map<sgx_enclave_id_t, dh_session_t>g_src_session_info_map;

static uint32_t e2_foo1_wrapper(ms_in_msg_exchange_t *ms, size_t param_lenth, char** resp_buffer, size_t* resp_length);

static uint32_t encrypt_enc_key_with_dev_key(ms_in_msg_exchange_t *ms, size_t param_lenth, char** resp_buffer, size_t* resp_length);

//Function pointer table containing the list of functions that the enclave exposes
const struct {
    size_t num_funcs;
    const void* table[2];
} func_table = {
    2,
    {
        (const void*)e2_foo1_wrapper,
		(const void*)encrypt_enc_key_with_dev_key,
    }
};
//Makes use of the sample code function to establish a secure channel with the destination enclave
uint32_t test_create_session(sgx_enclave_id_t src_enclave_id,
                          sgx_enclave_id_t dest_enclave_id)
{
    ATTESTATION_STATUS ke_status = SUCCESS;
    dh_session_t dest_session_info;
    //Core reference code function for creating a session
    ke_status = create_session(src_enclave_id, dest_enclave_id,&dest_session_info);
    if(ke_status == SUCCESS)
    {
        //Insert the session information into the map under the corresponding destination enclave id
        g_src_session_info_map.insert(std::pair<sgx_enclave_id_t, dh_session_t>(dest_enclave_id, dest_session_info));
    }
    memset(&dest_session_info, 0, sizeof(dh_session_t));
    return ke_status;
}

//Makes use of the sample code function to do an enclave to enclave call (Test Vector)
uint32_t test_enclave_to_enclave_call(sgx_enclave_id_t src_enclave_id,
                                          sgx_enclave_id_t dest_enclave_id)
{
    ATTESTATION_STATUS ke_status = SUCCESS;
    param_struct_t *p_struct_var, struct_var;
    uint32_t target_fn_id, msg_type;
    char* marshalled_inp_buff;
    size_t marshalled_inp_buff_len;
    char* out_buff;
    size_t out_buff_len;
    dh_session_t *dest_session_info;
    size_t max_out_buff_size;
    char* retval;

    max_out_buff_size = 50;
    target_fn_id = 0;
    msg_type = ENCLAVE_TO_ENCLAVE_CALL;

    struct_var.var1 = 0x3;
    struct_var.var2 = 0x4;
    p_struct_var = &struct_var;

    //Marshals the input parameters for calling function foo1 in Enclave3 into a input buffer
    ke_status = marshal_input_parameters_e3_foo1(target_fn_id, msg_type, p_struct_var, &marshalled_inp_buff, &marshalled_inp_buff_len);
    if(ke_status != SUCCESS)
    {
        return ke_status;
    }

    //Search the map for the session information associated with the destination enclave id passed in
    std::map<sgx_enclave_id_t, dh_session_t>::iterator it = g_src_session_info_map.find(dest_enclave_id);
    if(it != g_src_session_info_map.end())
    {
         dest_session_info = &it->second;
    }
    else
    {
        SAFE_FREE(marshalled_inp_buff);
        return INVALID_SESSION;
    }

    //Core Reference Code function
    ke_status = send_request_receive_response(src_enclave_id, dest_enclave_id, dest_session_info, marshalled_inp_buff,
                                               marshalled_inp_buff_len, max_out_buff_size, &out_buff, &out_buff_len);

    if(ke_status != SUCCESS)
    {
        SAFE_FREE(marshalled_inp_buff);
        SAFE_FREE(out_buff);
        return ke_status;
    }

    //Un-marshal the return value and output parameters from foo1 of Enclave3
    ke_status = unmarshal_retval_and_output_parameters_e3_foo1(out_buff, p_struct_var, &retval);
    if(ke_status != SUCCESS)
    {
        SAFE_FREE(marshalled_inp_buff);
        SAFE_FREE(out_buff);
        return ke_status;
    }

    SAFE_FREE(marshalled_inp_buff);
    SAFE_FREE(out_buff);
    SAFE_FREE(retval);
    return SUCCESS;
}

//Makes use of the sample code function to do a generic secret message exchange (Test Vector)
uint32_t test_message_exchange(sgx_enclave_id_t src_enclave_id,
                               sgx_enclave_id_t dest_enclave_id)
{
    ATTESTATION_STATUS ke_status = SUCCESS;
    uint32_t target_fn_id, msg_type;
    char* marshalled_inp_buff;
    size_t marshalled_inp_buff_len;
    char* out_buff;
    size_t out_buff_len;
    dh_session_t *dest_session_info;
    size_t max_out_buff_size;
    char* secret_response;
    uint32_t secret_data;

    target_fn_id = 0;
    msg_type = MESSAGE_EXCHANGE;
    max_out_buff_size = 50;
    secret_data = 0x12345678; //Secret Data here is shown only for purpose of demonstration.

    //Marshals the secret data into a buffer
    ke_status = marshal_message_exchange_request(target_fn_id, msg_type, secret_data, &marshalled_inp_buff, &marshalled_inp_buff_len);
    if(ke_status != SUCCESS)
    {
        return ke_status;
    }
    //Search the map for the session information associated with the destination enclave id passed in
    std::map<sgx_enclave_id_t, dh_session_t>::iterator it = g_src_session_info_map.find(dest_enclave_id);
    if(it != g_src_session_info_map.end())
    {
           dest_session_info = &it->second;
    }
    else
    {
        SAFE_FREE(marshalled_inp_buff);
        return INVALID_SESSION;
    }

    //Core Reference Code function
    ke_status = send_request_receive_response(src_enclave_id, dest_enclave_id, dest_session_info, marshalled_inp_buff,
                                                marshalled_inp_buff_len, max_out_buff_size, &out_buff, &out_buff_len);
    if(ke_status != SUCCESS)
    {
        SAFE_FREE(marshalled_inp_buff);
        SAFE_FREE(out_buff);
        return ke_status;
    }

    //Un-marshal the secret response data
    ke_status = umarshal_message_exchange_response(out_buff, &secret_response);
    if(ke_status != SUCCESS)
    {
        SAFE_FREE(marshalled_inp_buff);
        SAFE_FREE(out_buff);
        return ke_status;
    }

    SAFE_FREE(marshalled_inp_buff);
    SAFE_FREE(out_buff);
    SAFE_FREE(secret_response);
    return SUCCESS;
}


//Makes use of the sample code function to close a current session
uint32_t test_close_session(sgx_enclave_id_t src_enclave_id,
                                sgx_enclave_id_t dest_enclave_id)
{
    dh_session_t dest_session_info;
    ATTESTATION_STATUS ke_status = SUCCESS;
    //Search the map for the session information associated with the destination enclave id passed in
    std::map<sgx_enclave_id_t, dh_session_t>::iterator it = g_src_session_info_map.find(dest_enclave_id);
    if(it != g_src_session_info_map.end())
    {
         dest_session_info = it->second;
    }
    else
    {
        return NULL;
    }
    //Core reference code function for closing a session
    ke_status = close_session(src_enclave_id, dest_enclave_id);

    //Erase the session information associated with the destination enclave id
    g_src_session_info_map.erase(dest_enclave_id);
    return ke_status;
}

//Function that is used to verify the trust of the other enclave
//Each enclave can have its own way verifying the peer enclave identity
extern "C" uint32_t verify_peer_enclave_trust(sgx_dh_session_enclave_identity_t* peer_enclave_identity)
{
    if(!peer_enclave_identity)
    {
        return INVALID_PARAMETER_ERROR;
    }
    if(peer_enclave_identity->isv_prod_id != 0 || !(peer_enclave_identity->attributes.flags & SGX_FLAGS_INITTED))
        // || peer_enclave_identity->attributes.xfrm !=3)// || peer_enclave_identity->mr_signer != xx //TODO: To be hardcoded with values to check
    {
        return ENCLAVE_TRUST_ERROR;
    }
    else
    {
        return SUCCESS;
    }
}

//Dispatch function that calls the approriate enclave function based on the function id
//Each enclave can have its own way of dispatching the calls from other enclave
extern "C" uint32_t enclave_to_enclave_call_dispatcher(char* decrypted_data,
                                                       size_t decrypted_data_length,
                                                       char** resp_buffer,
                                                       size_t* resp_length)
{
    ms_in_msg_exchange_t *ms;
    uint32_t (*fn1)(ms_in_msg_exchange_t *ms, size_t, char**, size_t*);
    if(!decrypted_data || !resp_length)
    {
        return INVALID_PARAMETER_ERROR;
    }
    ms = (ms_in_msg_exchange_t *)decrypted_data;
    if(ms->target_fn_id >= func_table.num_funcs)
    {
        return INVALID_PARAMETER_ERROR;
    }
    fn1 = (uint32_t (*)(ms_in_msg_exchange_t*, size_t, char**, size_t*))func_table.table[ms->target_fn_id];
    return fn1(ms, decrypted_data_length, resp_buffer, resp_length);
}

//Operates on the input secret and generates the output secret
uint32_t get_message_exchange_response(uint32_t inp_secret_data)
{
    uint32_t secret_response;

    //User should use more complex encryption method to protect their secret, below is just a simple example
    secret_response = inp_secret_data & 0x11111111;

    return secret_response;

}

//Generates the response from the request message
extern "C" uint32_t message_exchange_response_generator(char* decrypted_data,
                                              char** resp_buffer,
                                               size_t* resp_length)
{
    ms_in_msg_exchange_t *ms;
    uint32_t inp_secret_data;
    uint32_t out_secret_data;
    if(!decrypted_data || !resp_length)
    {
        return INVALID_PARAMETER_ERROR;
    }
    ms = (ms_in_msg_exchange_t *)decrypted_data;

    if(umarshal_message_exchange_request(&inp_secret_data,ms) != SUCCESS)
        return ATTESTATION_ERROR;

    out_secret_data = get_message_exchange_response(inp_secret_data);

    if(marshal_message_exchange_response(resp_buffer, resp_length, out_secret_data) != SUCCESS)
        return MALLOC_ERROR;

    return SUCCESS;

}

static uint32_t e2_foo1(uint32_t var1, uint32_t var2)
{
    return(var1 + var2);
}

static void encrypt_key(uint8_t* key, uint8_t* encrypted_key)
{
	//encrypt key and put it on encrypted_key
	//not implemented yet.
	//memcpy(encrypted_key, key, KEY_SIZE);
	uint8_t p_ctr[32];
	sgx_aes_ctr_128bit_key_t device_key;
	uint32_t ctr_inc_bits = 1;
	uint8_t dec_key[KEY_SIZE];

	int i;
	for(i=0; i<32; i++)
		p_ctr[i]=0x11;
	memcpy(device_key, p_ctr, 16);
	/*
	for(i=0; i<32; i++)
	{
		device_key[i] = 0x11;
	}
*/

	memcpy(dec_key, key, sizeof(uint8_t)*KEY_SIZE);

	sgx_aes_ctr_encrypt(&device_key, (uint8_t*) key, KEY_SIZE,\
						p_ctr, ctr_inc_bits, (uint8_t*)encrypted_key);


	//check
	//uint8_t dec_key[KEY_SIZE];
	/*
	for(i=0; i<32; i++)
			p_ctr[i]=0x11;
	memcpy(dec_key, encrypted_key, sizeof(uint8_t)*KEY_SIZE);

	sgx_aes_ctr_decrypt(&device_key, (uint8_t*) encrypted_key, KEY_SIZE,\
						p_ctr, ctr_inc_bits, (uint8_t*)dec_key);
*/
}
//Function which is executed on request from the source enclave
static uint32_t e2_foo1_wrapper(ms_in_msg_exchange_t *ms,
                    size_t param_lenth,
                    char** resp_buffer,
                    size_t* resp_length)
{
    UNUSED(param_lenth);

    uint32_t var1,var2,ret;
    if(!ms || !resp_length)
    {
        return INVALID_PARAMETER_ERROR;
    }
    if(unmarshal_input_parameters_e2_foo1(&var1, &var2, ms) != SUCCESS)
        return ATTESTATION_ERROR;

    ret = e2_foo1(var1, var2);

    if(marshal_retval_and_output_parameters_e2_foo1(resp_buffer, resp_length, ret) != SUCCESS )
        return MALLOC_ERROR; //can set resp buffer to null here

    return SUCCESS;
}

//Function which is executed on request from the source enclave
static uint32_t encrypt_enc_key_with_dev_key(ms_in_msg_exchange_t *ms,
                    size_t param_lenth,
                    char** resp_buffer,
                    size_t* resp_length)
{
    UNUSED(param_lenth);

	uint8_t key[16];
	uint8_t encrypted_key[16];
    //uint32_t var1,var2,ret;
    if(!ms || !resp_length)
    {
        return INVALID_PARAMETER_ERROR;
    }
    //if(unmarshal_input_parameters_e2_foo1(&var1, &var2, ms) != SUCCESS)
    if(unmarshal_input_parameters_encrypt_key(key, ms) != SUCCESS)
        return ATTESTATION_ERROR;

    encrypt_key(key, encrypted_key);
    //ret = e2_foo1(var1, var2);

//iif(marshal_retval_and_output_parameters_e2_foo1(resp_buffer, resp_length, ret) != SUCCESS )
    if(marshal_retval_and_output_parameters_encrypt_key(resp_buffer, resp_length, encrypted_key) != SUCCESS )
        return MALLOC_ERROR; //can set resp buffer to null here

    return SUCCESS;
}
