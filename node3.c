#include <stdio.h>

extern struct rtpkt {
  int sourceid;       /* id of sending router sending this pkt */
  int destid;         /* id of router to which pkt being sent 
                         (must be an immediate neighbor) */
  int mincost[4];    /* min cost to node 0 ... 3 */
  };

extern int TRACE;
extern int YES;
extern int NO;

struct distance_table 
{
  int costs[4][4];
} dt3;

/* students to write the following two routines, and maybe some others */

void printdt3(struct distance_table *dtptr);

void rtinit3() 
{
  for (int i = 0; i < 4; ++i) {
    for (int j = 0; j < 4; ++j) {
      dt3.costs[i][j] = 999;
    }
  }

  printf("init3\n");
  dt3.costs[0][0] = 3;
  dt3.costs[1][1] = 999;
  dt3.costs[2][2] = 9;
  dt3.costs[3][3] = 0;

  for (int neighborID = 0; neighborID < 4; ++neighborID) {
        struct rtpkt updatePacket;
      
        updatePacket.sourceid = 3;
        updatePacket.destid = neighborID;

        for (int i = 0; i < 4; ++i) {
          updatePacket.mincost[i] = dt3.costs[i][i];
        }
      tolayer2(updatePacket);
      }
}


void rtupdate3(struct rtpkt *rcvdpkt) {
  printf("Entering rtupdate3\n");
  int source = rcvdpkt->sourceid;
  int dest = rcvdpkt->destid;

  if (dest == 3) { 
    int updateChecker = 0;

    for (int i = 0; i < 4; ++i) {
      int newCost = dt3.costs[source][source] + rcvdpkt->mincost[i];

      if (newCost < dt3.costs[i][source]) {
        printf("Path Update Update3: %d -> %d at [%d, %d]\n", dt3.costs[i][source], newCost, source, i);
        dt3.costs[i][source] = newCost;
        updateChecker = 1;
      }
    }

  for (int dest = 0; dest < 4; ++dest) {
    if (dest != source && dest != rcvdpkt->sourceid) {
      int newCost = dt3.costs[source][source] + rcvdpkt->mincost[dest];

      if (newCost < dt3.costs[source][dest]) {
        dt3.costs[source][dest] = newCost;
        updateChecker = 1;
        }
      }
    }

    if (updateChecker == 1) {
      printdt3(&dt3);

      for (int neighborID = 0; neighborID < 4; ++neighborID) {
        struct rtpkt updatePacket;

        updatePacket.sourceid = 3;
        updatePacket.destid = neighborID;

        for (int i = 0; i < 4; ++i) {
          updatePacket.mincost[i] = dt3.costs[source][i];
        }
        printf("Packet sent from %d to %d\n", updatePacket.sourceid, neighborID);
        tolayer2(updatePacket);
      }
    }
  printdt3(&dt3);
  }
}



void printdt3(dtptr)
  struct distance_table *dtptr;
  
{
  printf("             via     \n");
  printf("   D3 |    0     2 \n");
  printf("  ----|-----------\n");
  printf("     0|  %3d   %3d\n",dtptr->costs[0][0], dtptr->costs[0][2]);
  printf("dest 1|  %3d   %3d\n",dtptr->costs[1][0], dtptr->costs[1][2]);
  printf("     2|  %3d   %3d\n",dtptr->costs[2][0], dtptr->costs[2][2]);

}







