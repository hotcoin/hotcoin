// Copyright (c) 2013 NovaCoin Developers

#ifndef RPCWALLET_H
#define RPCWALLET_H

#include "uint256.h"

#include <stdarg.h>

#ifndef WIN32
#include <sys/types.h>
#include <sys/time.h>
#include <sys/resource.h>
#endif
#include <map>
#include <list>
#include <utility>
#include <vector>
#include <string>

#include "wallet.h"
#include "walletdb.h"
#include "bitcoinrpc.h"
#include "init.h"
#include "base58.h" 

int64 GetAccountBalance(const std::string& strAccount, int nMinDepth = 1);
std::string GetAddressesByAccount(const std::string& strAccount);
std::string GetAccount(const std::string& strAddr);
#endif // RPCWALLET_H
