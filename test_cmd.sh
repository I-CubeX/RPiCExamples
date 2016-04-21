#trap ctrl_c
trap ctrl_c INT

function ctrl_c() {
   echo "exiting..."

   i2cset -y 1 0x09 0x70 0x00 0x00 0x00 i # play default script

   exit 0
}


#stop existing script first
i2cset -y 1 0x09 0x01 0x6F i

#make the blinkM flash a bit...
for ((i=0;i<4;i++)); do
  i2cset -y 1 0x09 0x01 0x63 0xff 0x00 0x00 i # RED
  sleep 0.1
  i2cset -y 1 0x09 0x01 0x63 0x00 0xff 0x00 i # GREEN
  sleep 0.1
  i2cset -y 1 0x09 0x01 0x63 0x00 0x00 0xff i # BLUE
  sleep 0.1
done

while true; do
  VAL=`gpio -x mcp3004:100:0 aread 100`
  BRI=`gpio -x mcp3004:100:0 aread 101`
  A=`expr $VAL / 2 + 10`
  if [ "$A" -gt 255 ];
  then
     A=255
  fi
  BRI=`expr $BRI / 4`
  echo col = $A  bri = $BRI;
  R=`expr $A \* $BRI / 255`
  B=`expr 255 - $A`
  B=`expr $B \* $BRI / 255`
  G=0 
  i2cset -y 1 0x09 0x01 0x6e $R $G $B i #set brightness according to sensor value
  sleep 0.02
  
  
done

