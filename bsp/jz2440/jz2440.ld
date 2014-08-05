;;
;; Copyright (C) 2014 Huang Bo
;;

load 0x00000000 0x00001000 {
     nor_nand 0x00000000 0x00001000 {
     	      start_armcc.o (init, +FIRST)     
	      * (+RO, +RW, +ZI)
     }
}
