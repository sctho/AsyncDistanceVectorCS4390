#include <stdio.h>

struct rtpkt {
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
} dt2;

void printdt2(struct distance_table *dtptr);

/* students to write the following two routines, and maybe some others */

void rtinit2() 
{
  for (int i = 0; i < 4; ++i) {
    for (int j = 0; j < 4; ++j) {
      dt2.costs[i][j] = 999;
    }
  }

  

  printf("init2\n");
  dt2.costs[0][0] = 5;
  dt2.costs[1][1] = 2;
  dt2.costs[2][2] = 0;
  dt2.costs[3][3] = 9;

  for (int neighborID = 0; neighborID < 4; ++neighborID) {
        struct rtpkt updatePacket;
      
        updatePacket.sourceid = 2;
        updatePacket.destid = neighborID;

        for (int i = 0; i < 4; ++i) {
          updatePacket.mincost[i] = dt2.costs[i][i];
        }
      tolayer2(updatePacket);
      }

}


void rtupdate2(rcvdpkt)
  struct rtpkt *rcvdpkt;
{
  printf("Entered rtupdate2\n");
  int source = rcvdpkt->sourceid;
  int dest = rcvdpkt->destid;

  if (dest == 2) {
    int updateChecker = 0;

    for (int i = 0; i < 4; ++i) {
      int newCost = dt2.costs[source][source] + rcvdpkt->mincost[i];

      if (newCost < dt2.costs[i][source]) {
        printf("Path Update Update2: %d -> %d at [%d, %d]\n", dt2.costs[i][source], newCost, source, i);
        dt2.costs[i][source] = newCost;

        updateChecker = 1;
      }
    }

    for (int dest = 0; dest < 4; ++dest) {
    if (dest != source && dest != rcvdpkt->sourceid) {
      int newCost = dt2.costs[source][source] + rcvdpkt->mincost[dest];

      if (newCost < dt2.costs[source][dest]) {
        dt2.costs[source][dest] = newCost;
        updateChecker = 1;
        }
      }
    } 

    if (updateChecker == 1) {
      //printdt2(&dt2);

      for (int neighborID = 0; neighborID < 4; ++neighborID) {
        struct rtpkt updatePacket;
      
        updatePacket.sourceid = 2;
        updatePacket.destid = neighborID;

        for (int i = 0; i < 4; ++i) {
          updatePacket.mincost[i] = dt2.costs[source][i];
        }
      printf("Packet sent from %d to %d\n", updatePacket.sourceid, neighborID);
      tolayer2(updatePacket);
      }
      //printdt2(&dt2);
    }
    printdt2(&dt2);
  }
}


void printdt2(dtptr)
  struct distance_table *dtptr;
  
{
  printf("                via     \n");
  printf("   D2 |    0     1    3 \n");
  printf("  ----|-----------------\n");
  printf("     0|  %3d   %3d   %3d\n",dtptr->costs[0][0],
	 dtptr->costs[0][1],dtptr->costs[0][3]);
  printf("dest 1|  %3d   %3d   %3d\n",dtptr->costs[1][0],
	 dtptr->costs[1][1],dtptr->costs[1][3]);
  printf("     3|  %3d   %3d   %3d\n",dtptr->costs[3][0],
	 dtptr->costs[3][1],dtptr->costs[3][3]);
}







