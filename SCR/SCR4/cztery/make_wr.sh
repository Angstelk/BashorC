#/!/bin/bash
echo tworze pipe
mknod p fifo
echo pisze do potoku
while true; do echo "Pustono ludo i mlado
       ishte mi, maycho, armagan /2
chornise ochi da mu dam.
Dali da gi dam, che kak da gi dam,
ga ma mayka glyoda ottam?
Pustono ludo i mlado
ishte mi, maycho, armagan/2"  > fifo ; done


