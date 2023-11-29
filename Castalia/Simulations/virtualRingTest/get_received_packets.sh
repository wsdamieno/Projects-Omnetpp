#!/bin/bash

# For use with Castalia
#
# Author: Alba Rozas Cid
# B105 Electronic Systems Lab
# Universidad Politécnica de Madrid
#
# albarc@b105.upm.es
#

# Pide dos argumentos, el primero es el id del nodo inicial y el segundo el del nodo final de los que son fuente de paquetes.
# Es decir, si por ejemplo el 0 es el sink, y el 1,2,3,4 son routers, pues se debería poner como nodo inicial el
# 5. El numero del nodo final siempre es el numero total de nodos en el escenario menos 1 (porque se empieza a contar por 0).

echo "Paquetes recibidos en el sink"

let A=0
let C=0
let ORIGPRIOR1=0
let ORIGPRIOR2=0
let ORIGPRIOR3=0
let ORIGPRIOR4=0

for ((k=$1;k<=$2;k++)); do
	echo "Nodo $k: "
	grep 'Received packet #' Castalia-Trace.txt | grep "from node $k$" | wc -l
	A=`expr $(grep 'Received packet #' Castalia-Trace.txt | grep 'SN.node\[0\].Application' | grep "from node $k$" | wc -l) + $A`
done

let B=`expr $2 - $1 + 1`
echo "  "
echo "XXXXXXXXXXXXXXXX"
echo "XX  Media: `expr $A / $B`  XX"
echo "XXXXXXXXXXXXXXXX"
echo "  "

: <<'END'
for ((k=$1;k<$2;k++)); do
	if [ $k -ne $ORIGPRIOR1 ] && [ $k -ne $ORIGPRIOR2 ] && [ $k -ne $ORIGPRIOR3 ] && [ $k -ne $ORIGPRIOR4 ]; then
		echo "Nodo $k: "
		grep 'Received packet #' Castalia-Trace.txt | grep "from node $k$" | wc -l
		A=`expr $(grep 'Received packet #' Castalia-Trace.txt | grep 'SN.node\[0\].Application' | grep "from node $k$" | wc -l) + $A`
	else
		echo "Nodo prioritario $k: "
		grep 'Received packet #' Castalia-Trace.txt | grep "from node $k$" | wc -l
		C=`expr $(grep 'Received packet #' Castalia-Trace.txt | grep 'SN.node\[0\].Application' | grep "from node $k$" | wc -l) + $C`
	fi
done

let B=`expr $2 - $1`
echo "Media por origen (no prioritario): `expr $A / $B`"
echo "Media por origen (prioritario): `expr $C / 4`"

for ((k=0;k<4;k++)); do 
	echo "Nivel de prioridad $k: "
	grep 'Received packet #' Castalia-Trace.txt | grep 'SN.node\[0\].Application' | grep "with priority level $k" | wc -l 
done
END
