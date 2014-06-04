// Copyright (c) 2009-2012 The Bitcoin developers
// Distributed under the MIT/X11 software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include <boost/assign/list_of.hpp> // for 'map_list_of()'
#include <boost/foreach.hpp>

#include "checkpoints.h"

#include "main.h"
#include "uint256.h"

namespace Checkpoints
{
    typedef std::map<int, uint256> MapCheckpoints;

    // How many times we expect transactions after the last checkpoint to
    // be slower. This number is a compromise, as it can't be accurate for
    // every system. When reindexing from a fast disk with a slow CPU, it
    // can be up to 20, while when downloading from a slow network with a
    // fast multicore CPU, it won't be much higher than 1.
    static const double fSigcheckVerificationFactor = 5.0;

    struct CCheckpointData {
        const MapCheckpoints *mapCheckpoints;
        int64 nTimeLastCheckpoint;
        int64 nTransactionsLastCheckpoint;
        double fTransactionsPerDay;
    };

    // What makes a good checkpoint block?
    // + Is surrounded by blocks with reasonable timestamps
    //   (no blocks before with a timestamp after, none after with
    //    timestamp before)
    // + Contains no strange transactions
    static MapCheckpoints mapCheckpoints =
        boost::assign::map_list_of
        (  1, uint256("0x5fdf4ec757ab6e29753b7f358a9d1fa246d7792b815171f9d8657de379b0fd07"))
        (  2, uint256("0xa038b3ed2c64e9ed79b4f56390f3a9e3510ba8788b549e0d47571001839abaf2"))		
        (  500, uint256("0x3b20532e51b504931ef29134dacad478a0501e8b3cecb20a811df9e49612fa80"))				
        (  1000, uint256("0x9d56296778574ba0b0e6c83af180c55dd12b335bc9677d8c06e3e0a0b4560444"))						
        (  5000, uint256("0x2204f15655cb9a0328a71ce63187417e7cd5f2f0f6892a4ec9cf2692c7adfa4c"))								
        (  10000, uint256("0x000a84c64c5d070493a0a9934958d3615248a4733d050411df4d8a7b04391837"))
        (  15000, uint256("0x79b575113ebce83eba5e67c9b6012fe1baef65daa2980b1ebb06aaf81ad26938"))		
        (  20000, uint256("0xa886b750ff1ffa03def7a5cffe57c6dae0fccb4e52d1fc1b28953bd134eb002b"))				
        (  25000, uint256("0xa5aea4aa98965005cf3bc0cdf7fdd810210d2eab3dd3c55c193e5673bfabb01a"))						
		(  30000, uint256("0x4f266d69940bc71d88556c7f528eb19a2a997feecfe7cfa687d587671d997d41"))
		(  35000, uint256("0xda1affb55fe48d52c0dbda46ec920a453c2583219d6a7a3dc51ab02c0e92b8ac"))
		(  40000, uint256("0xd17cd741052f3dc2cf789deab98e252ebae6041e953dd6ba3fef025c9c847862"))
		(  50000, uint256("0x9b9b7d91b255759135d75f498160220d5b8d1332fd35084f456df45222950353"))
		(  55000, uint256("0x7f384822f59115a099a20efaeac96637e42e527a9a8b826ea29cef7b585d8700"))
		(  60000, uint256("0x016df74efefeeea55e3af5f48f36f9f0be61d4c68bcd89418575ead2d721e77e"))
		(  65000, uint256("0x0abf20a4f64aef5eeefef86742487698f7b37489115f1f819f001fd4393a5c4c"))
		(  70000, uint256("0x329458d6ec5fa7af6ed4c239d955cf27b49ecf0268e1b12f2eef8c205134f17d"))
		(  75000, uint256("0xce1efb6baf2e51084f99b967c1e8bbf1f4f31beec86a58c58875906355804553"))
		(  80000, uint256("0x9f197690732518d7735b4553c3647aeffc995df402e7b6075e90f244ca997ff7"))
		(  90000, uint256("0x4b39d7ca068b0c8b69e11d518bfdf2d29f1c27cfdbc3d781fa22c56a0f92c829"))
		(  95000, uint256("0x7c558f594923a5a4ce374ecdb00f70e88145eea0151200032df90b39849d9ca4"))
		(  100000, uint256("0xe1099528345cc16363a6014f6f29c52e2b17db6dbbb79b126b1b6685a1785fbf"))
		(  110000, uint256("0x4b03b6bb9f5abe6341ea5e6be092432f7d80bdf9c99a10af9fa55708442304a8"))
		(  120000, uint256("0xe1596c0f13ec4d4b058ae4a4d95e6207bc7cf2943903d4d54c1c0da8d97e5886"))
        ;
    static const CCheckpointData data = {
        &mapCheckpoints,
        1399415490, // * UNIX timestamp of last checkpoint block
        120000,    // * total number of transactions between genesis and last checkpoint
                    //   (the tx=... number in the SetBestChain debug.log lines)
        8000.0     // * estimated number of transactions per day after checkpoint
    };

    static MapCheckpoints mapCheckpointsTestnet = 
        boost::assign::map_list_of
        (   546, uint256("000000002a936ca763904c3c35fce2f3556c559c0214345d31b1bcebf76acb70"))
        ;
    static const CCheckpointData dataTestnet = {
        &mapCheckpointsTestnet,
        1369685559,
        16341,
        300
    };

    const CCheckpointData &Checkpoints() {
        if (fTestNet)
            return dataTestnet;
        else
            return data;
    }

    bool CheckBlock(CValidationState &state, int nHeight, const uint256& hash)
    {
		if (fTestNet) return true; // Testnet has no checkpoints
        if (!GetBoolArg("-checkpoints", true))
            return true;

        const MapCheckpoints& checkpoints = *Checkpoints().mapCheckpoints;

        MapCheckpoints::const_iterator i = checkpoints.find(nHeight);
        if (i == checkpoints.end()) return true;
        return hash == i->second;
    }

    // Guess how far we are in the verification process at the given block index
    double GuessVerificationProgress(CBlockIndex *pindex) {
        if (pindex==NULL)
            return 0.0;

        int64 nNow = time(NULL);

        double fWorkBefore = 0.0; // Amount of work done before pindex
        double fWorkAfter = 0.0;  // Amount of work left after pindex (estimated)
        // Work is defined as: 1.0 per transaction before the last checkoint, and
        // fSigcheckVerificationFactor per transaction after.

        const CCheckpointData &data = Checkpoints();

        if (pindex->nChainTx <= data.nTransactionsLastCheckpoint) {
            double nCheapBefore = pindex->nChainTx;
            double nCheapAfter = data.nTransactionsLastCheckpoint - pindex->nChainTx;
            double nExpensiveAfter = (nNow - data.nTimeLastCheckpoint)/86400.0*data.fTransactionsPerDay;
            fWorkBefore = nCheapBefore;
            fWorkAfter = nCheapAfter + nExpensiveAfter*fSigcheckVerificationFactor;
        } else {
            double nCheapBefore = data.nTransactionsLastCheckpoint;
            double nExpensiveBefore = pindex->nChainTx - data.nTransactionsLastCheckpoint;
            double nExpensiveAfter = (nNow - pindex->nTime)/86400.0*data.fTransactionsPerDay;
            fWorkBefore = nCheapBefore + nExpensiveBefore*fSigcheckVerificationFactor;
            fWorkAfter = nExpensiveAfter*fSigcheckVerificationFactor;
        }

        return fWorkBefore / (fWorkBefore + fWorkAfter);
    }

    int GetTotalBlocksEstimate()
    {
        if (fTestNet) return 0; // Testnet has no checkpoints
        if (!GetBoolArg("-checkpoints", true))
            return 0;

        const MapCheckpoints& checkpoints = *Checkpoints().mapCheckpoints;

        return checkpoints.rbegin()->first;
    }

    CBlockIndex* GetLastCheckpoint(const std::map<uint256, CBlockIndex*>& mapBlockIndex)
    {
        if (fTestNet) return NULL; // Testnet has no checkpoints
        if (!GetBoolArg("-checkpoints", true))
            return NULL;

        const MapCheckpoints& checkpoints = *Checkpoints().mapCheckpoints;

        BOOST_REVERSE_FOREACH(const MapCheckpoints::value_type& i, checkpoints)
        {
            const uint256& hash = i.second;
            std::map<uint256, CBlockIndex*>::const_iterator t = mapBlockIndex.find(hash);
            if (t != mapBlockIndex.end())
                return t->second;
        }
        return NULL;
    }
}
