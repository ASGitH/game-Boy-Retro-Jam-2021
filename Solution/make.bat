@echo off
c:\gbdk\bin\lcc -Wa-l -Wl-m -Wf--debug -Wl-y -Wl-w -c -o main.o main.c
c:\gbdk\bin\lcc -Wa-l -Wl-m -Wf--debug -Wl-y -Wl-w -o main.gb main.o backgrounds/headsUpDisplayMB.c gameConfiguration.c guard.c headsUpDisplay.c player.c projectile.c sprites\fontTD.c sprites\guardTD.c sprites\miscellaneous.c sprites\playerTD.c