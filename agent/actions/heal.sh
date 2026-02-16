#!/bin/bash

# buang semua cache (1=pagecache, 2=pagecache dentries, 3=inodes(all))
echo "[SENTIX] Cleaning cache..."
sync
sh -c 'echo 3 >  /proc/sys/vm/drop_caches'
echo "[SENTIX] Done cleaning cache."
