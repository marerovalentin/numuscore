Numus core info

Numus is a PoW/PoS Hybrid cryptocurrency.

PoW Algo - Skein

Reward Scheme:

// Sunrise Release
100 000 - 150 000 | 10 NMS ~30d

// Rhizocarpon Release (Pure POS)
150 000 - 200 000 | 6 NMS ~30d
200 000 - 250 000 | 5 NMS ~30d
250 000 - 300 000 | 4 NMS ~30d
300 000 - 350 000 | 3 NMS ~30d
350 000 - 400 000 | 2 NMS ~30d

// Bryopsida Release (temporary release Hybrid POW/POS)
POW Return (MN Will receive 75% of POS block rewards)
400 000 - 500 000 | POW 1.5 NMS / POS 1 NMS ~60d 


// Harvest Moon Release (POW only , Reward plan will be reworked)
500 000 - 600 000 | POW 1 NMS ~60d 
600 000 - 700 000 | POW 0.75 NMS ~60d

// Dallia Release (POW only)
700 000 - 1 300 000 | POW 0.5 NMS  ~ 180d

Maximum Amount of Coins: 6 500 000 NMS

Masternode Collaterial - 5 000 NMS.
Masternodes Rewards:
0 - 700 000 | 75% of POS Blocks


Block Spacing: 45 Seconds
Diff Retarget: 5 Blocks
Maturity: 30 Blocks
Stake Minimum Age: 24 Hours

Port: 28121
RPC Port: 28122

40 MegaByte Maximum Block Size (40X Bitcoin Core)

Numus is dependent upon libsecp256k1 by sipa, the sources for which can be found here:
https://github.com/bitcoin/secp256k1

Numus includes an Address Index feature, based on the address index API (searchrawtransactions RPC command) implemented in Bitcoin Core but modified implementation to work with the NMS codebase (PoS coins maintain a txindex by default for instance).

Initialize the Address Index By Running with -reindexaddr Command Line Argument.  It may take 10-15 minutes to build the initial index.
