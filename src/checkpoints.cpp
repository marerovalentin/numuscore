// Copyright (c) 2009-2012 The Bitcoin developers
// Distributed under the MIT/X11 software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include <boost/assign/list_of.hpp> // for 'map_list_of()'
#include <boost/foreach.hpp>

#include "checkpoints.h"

#include "txdb.h"
#include "main.h"
#include "uint256.h"


static const int nCheckpointSpan = 5000;

namespace Checkpoints
{
    typedef std::map<int, uint256> MapCheckpoints;

    //
    // What makes a good checkpoint block?
    // + Is surrounded by blocks with reasonable timestamps
    //   (no blocks before with a timestamp after, none after with
    //    timestamp before)
    // + Contains no strange transactions
    //
    static MapCheckpoints mapCheckpoints =
        boost::assign::map_list_of
     (     0, uint256("0x0711d3aa8846a5a90ab56f0653e066351080f095661c573a45cb94737a82c37c") )
     ( 10000, uint256("0x2c818ec5b23575dc14abc96081968f4ee265cc6ad924b67951d8749db9340e81") )
     ( 50000, uint256("0x538db4fcacb0c306b0775c8b1de631080d5dca61082908f3ed45d92f91768576") )
     ( 75000, uint256("0x0000000000000b5ffd71d398d0a3947e9bbdc809b64ddb617351e1be5df33fd3") )
     ( 100000, uint256("0xb7d8b3c84490e848bd91d24a4f3fdaf224212859899bd1340b9fec525244fd05") )
     ( 150000, uint256("0x1398171bccc056f92347e30a1268cee079654454b0ccd4ba0389d57992efd202") )
     ( 200000, uint256("0xbb7cde3689f19dfc6c5e601ddd2410e2f3c839c3b7d12ff58781d9d69204b924") )
     ( 210050, uint256("0xf50a19cb981b92b78da96e7a9504bf317bb17e0eabfbf5f124cdee28a2b953a5") )
	 ( 250100, uint256("0x81c82bb2fd4df344977aba372299fcf275d02cafcf82d5da0236dc59a3e3a642") )
	 ( 251400, uint256("0x97544b277c56eec6b2796f16d44c7086114b46b7da32d73b4501f849e96862c2") )
	 ( 252970, uint256("0x885f6a88e26bf71a98b463bbaedbbac8fa6ba6f874029cf45b8d4a294c6b9649") )
	 ( 258800, uint256("0xc95a85f29f68c72f060247dc532017dadcf9fade0110532f854ee25137d09a84") )
	 ( 400150, uint256("0xc96dbf7bcd01c2d97621e8e9a7a23afc48ddc37ecba68a697f1890ad95f5a253a") )
	 ( 400500, uint256("0x8b1112fce630d0f33d88553ce29d4612d5cf23489787c45d49f1ca745d6251cd") )
	 ( 401000, uint256("0x893f1137f336c3ab43b90e81befaf0f654de189179affd5b45e67d61682d4b71") )
	 ( 401750, uint256("0x6f3b82c5fdfb79269cf915bf670040e290a0ec2acf432e8d8bf226616c0c53d6") )
    ;

    // TestNet has no checkpoints
    static MapCheckpoints mapCheckpointsTestnet;

    bool CheckHardened(int nHeight, const uint256& hash)
    {
        MapCheckpoints& checkpoints = (TestNet() ? mapCheckpointsTestnet : mapCheckpoints);

        MapCheckpoints::const_iterator i = checkpoints.find(nHeight);
        if (i == checkpoints.end()) return true;
        return hash == i->second;
    }

    int GetTotalBlocksEstimate()
    {
        MapCheckpoints& checkpoints = (TestNet() ? mapCheckpointsTestnet : mapCheckpoints);

        if (checkpoints.empty())
            return 0;
        return checkpoints.rbegin()->first;
    }

    CBlockIndex* GetLastCheckpoint(const std::map<uint256, CBlockIndex*>& mapBlockIndex)
    {
        MapCheckpoints& checkpoints = (TestNet() ? mapCheckpointsTestnet : mapCheckpoints);

        BOOST_REVERSE_FOREACH(const MapCheckpoints::value_type& i, checkpoints)
        {
            const uint256& hash = i.second;
            std::map<uint256, CBlockIndex*>::const_iterator t = mapBlockIndex.find(hash);
            if (t != mapBlockIndex.end())
                return t->second;
        }
        return NULL;
    }

    // Automatically select a suitable sync-checkpoint 
    const CBlockIndex* AutoSelectSyncCheckpoint()
    {
        const CBlockIndex *pindex = pindexBest;
        // Search backward for a block within max span and maturity window
        while (pindex->pprev && pindex->nHeight + nCheckpointSpan > pindexBest->nHeight)
            pindex = pindex->pprev;
        return pindex;
    }

    // Check against synchronized checkpoint
    bool CheckSync(int nHeight)
    {
        const CBlockIndex* pindexSync = AutoSelectSyncCheckpoint();
        if (nHeight <= pindexSync->nHeight){
            return false;
        }
        return true;
    }
}
