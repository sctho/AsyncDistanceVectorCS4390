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

int connectcosts1[4] = { 1,  0,  1, 999 };

struct distance_table 
{
  int costs[4][4];
} dt1;

void printdt1(struct distance_table *dtptr);


/* students to write the following two routines, and maybe some others */


void rtinit1()
{
  for (int i = 0; i < 4; ++i) {
    for (int j = 0; j < 4; ++j) {
      dt1.costs[i][j] = 999;
    }
  }

  printf("init1\n");
  dt1.costs[0][0] = 2;
  dt1.costs[1][1] = 0;
  dt1.costs[2][2] = 2;
  dt1.costs[3][3] = 999;

  for (int neighborID = 0; neighborID < 4; ++neighborID) {
        struct rtpkt updatePacket;
      
        updatePacket.sourceid = 1;
        updatePacket.destid = neighborID;

        for (int i = 0; i < 4; ++i) {
          updatePacket.mincost[i] = dt1.costs[i][i];
        }
      tolayer2(updatePacket);
      }
}


void rtupdate1(rcvdpkt)
  struct rtpkt *rcvdpkt;
{
  printf("Entering rtupdate1\n");
  int source = rcvdpkt->sourceid;
  int dest = rcvdpkt->destid;

  if (dest == 1) {
    int updateChecker = 0;

    for (int i = 0; i < 4; ++i) {
      int newCost = dt1.costs[source][source] + rcvdpkt->mincost[i];

      if (newCost < dt1.costs[i][source]) {
        printf("Path Update Update1: %d -> %d at [%d, %d]\n", dt1.costs[i][source], newCost, source, i);
        dt1.costs[i][source] = newCost;

        updateChecker = 1;
      }
    }

    for (int dest = 0; dest < 4; ++dest) {
    if (dest != source && dest != rcvdpkt->sourceid) {
      int newCost = dt1.costs[source][source] + rcvdpkt->mincost[dest];

      if (newCost < dt1.costs[source][dest]) {
        dt1.costs[source][dest] = newCost;
        updateChecker = 1;
        }
      }
    } 

    if (updateChecker == 1) {
      //printdt1(&dt1);

      for (int neighborID = 0; neighborID < 4; ++neighborID) {
        struct rtpkt updatePacket;
      
        updatePacket.sourceid = 1;
        updatePacket.destid = neighborID;

        for (int i = 0; i < 4; ++i) {
          updatePacket.mincost[i] = dt1.costs[source][i];
        }
      printf("Packet sent from %d to %d\n", updatePacket.sourceid, neighborID);
      tolayer2(updatePacket);
      }
      //printdt1(&dt1);
    }
  printdt1(&dt1);
  }
}


void printdt1(dtptr)
  struct distance_table *dtptr;
  
{
  printf("             via   \n");
  printf("   D1 |    0     2 \n");
  printf("  ----|-----------\n");
  printf("     0|  %3d   %3d\n",dtptr->costs[0][0], dtptr->costs[0][2]);
  printf("dest 2|  %3d   %3d\n",dtptr->costs[2][0], dtptr->costs[2][2]);
  printf("     3|  %3d   %3d\n",dtptr->costs[3][0], dtptr->costs[3][2]);

}



void linkhandler1(linkid, newcost)
int linkid, newcost;   
/* called when cost from 1 to linkid changes from current value to newcost*/
/* You can leave this routine empty if you're an undergrad. If you want */
/* to use this routine, you'll need to change the value of the LINKCHANGE */
/* constant definition in prog3.c from 0 to 1 */
	
{
}


