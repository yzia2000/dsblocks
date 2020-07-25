#!/bin/dash
case "$1" in
    initiate)
        iwi=$(nmcli -t -f DEVICE connection show --active | head -n1)
        [ -z "$iwi" ] && iwi=eno1
        trap 'sigdsblocks 3 0; exit' EXIT HUP INT TERM
        sigdsblocks 3 1
        create_ap wlp5s0 "$iwi" hp 98761234
        ;;
    terminate)
        create_ap --stop wlp5s0
        ;;
    fix-unmanaged)
        [ "$(create_ap --list-running | wc -l)" -le 2 ] && create_ap --fix-unmanaged
        ;;
    *)
        echo "Usage: $0 initiate|terminate|fix-unmanaged"
    ;;
esac