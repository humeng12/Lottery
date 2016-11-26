//
//  connect.h
//  MyPOSHRT3
//
//  Created by Y on 14-9-26.
//  Copyright (c) 2014年 Y. All rights reserved.
//
#ifndef MyPOSHRT3_connect_h
#define MyPOSHRT3_connect_h

extern int iSocket;

/**
 *  @brief  连接姗姗的后台 iConnectTCPIPHost
 *
 *  @param szHostName IP地址
 *  @param nPort      端口号
 *  @param uiTimeOut  超时时间（单位秒）
 *
 *  @return -2 连接失败    0 连接成功
 */
int b19177539def0aacd028c1431978290b(const char *szHostName, unsigned int nPort, unsigned int uiTimeOut);

/**
 *  @brief  向后台发送数据并接收后台返回的数据  iSendReceive
 *
 *  @param i_uszSendPacket   发送的数据
 *  @param i_ulSendSize     发送的数据长度
 *  @param o_puszRecvPacket 接收到的数据
 *  @param i_pulRecvSize    接收到的数据长度
 *
 *  @return 1 发送失败    0 接收失败    >>0接收成功
 */
int af2d87ec65d7e992873c381e78ee17d7(unsigned char *i_uszSendPacket,int *i_ulSendSize,
                 unsigned char *o_puszRecvPacket,int *i_pulRecvSize);
/**
 *  @brief  向后台发送数据  iSendTCPIPData
 *
 *  @param i_pszData  发送的数据
 *  @param i_iLength 发送的数据长度
 *
 *  @return -5：发送失败
 */
int f472719992051827f84c213642172140(unsigned char *i_pszData, int i_iLength);

#endif
