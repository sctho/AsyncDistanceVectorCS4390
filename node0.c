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
} dt0;

void printdt0(struct distance_table *dtptr);

/* students to write the following two routines, and maybe some others */

void rtinit0() 
{
  for (int i = 0; i < 4; ++i) {
    for (int j = 0; j < 4; ++j) {
      dt0.costs[i][j] = 999;
    }
  }
  printf("init0\n");
  dt0.costs[0][0] = 0;
  dt0.costs[1][1] = 2;
  dt0.costs[2][2] = 5;
  dt0.costs[3][3] = 3;
  printf("0\n");

  for (int neighborID = 0; neighborID < 4; ++neighborID) {
        struct rtpkt updatePacket;
      
        updatePacket.sourceid = 0;
        updatePacket.destid = neighborID;

        for (int i = 0; i < 4; ++i) {
          updatePacket.mincost[i] = dt0.costs[i][i];
        }
      tolayer2(updatePacket);
      }
}

void rtupdate0(struct rtpkt *rcvdpkt)
  {
  printf("Entering rtupdate0\n");
  int source = rcvdpkt->sourceid;
  int dest = rcvdpkt->destid;

    int updateChecker = 0;

    for (int i = 0; i < 4; ++i) {
      int newCost = dt0.costs[source][source] + rcvdpkt->mincost[i];

      if (newCost < dt0.costs[i][source]) {
        printf("Path Update Update0: %d -> %d at [%d, %d]\n", dt0.costs[i][source], newCost, source, i);
        dt0.costs[i][source] = newCost;

        updateChecker = 1;
      }
    }

    for (int dest = 0; dest < 4; ++dest) {
    if (dest != source && dest != rcvdpkt->sourceid) {
      int newCost = dt0.costs[source][source] + rcvdpkt->mincost[dest];

      if (newCost < dt0.costs[source][dest]) {  
        dt0.costs[source][dest] = newCost;
        updateChecker = 1;
        }
      }
    } 

    if (updateChecker == 1) {
      //printdt0(&dt0);

      for (int neighborID = 0; neighborID < 4; ++neighborID) {
        struct rtpkt updatePacket;
      
        updatePacket.sourceid = 0;
        updatePacket.destid = neighborID;

        for (int i = 0; i < 4; ++i) {
          updatePacket.mincost[i] = dt0.costs[source][i];
        }
      printf("Packet sent from %d to %d\n", updatePacket.sourceid, neighborID);
      tolayer2(updatePacket);
      }
      //printdt0(&dt0);
    }
  printdt0(&dt0);
}


void printdt0(dtptr)
  struct distance_table *dtptr;
  
{
  printf("                via     \n");
  printf("   D0 |    1     2    3 \n");
  printf("  ----|-----------------\n");
  printf("     1|  %3d   %3d   %3d\n",dtptr->costs[1][1],
	 dtptr->costs[1][2],dtptr->costs[1][3]);
  printf("dest 2|  %3d   %3d   %3d\n",dtptr->costs[2][1],
	 dtptr->costs[2][2],dtptr->costs[2][3]);
  printf("     3|  %3d   %3d   %3d\n",dtptr->costs[3][1],
	 dtptr->costs[3][2],dtptr->costs[3][3]);
}

linkhandler0(linkid, newcost)   
  int linkid, newcost;

/* called when cost from 0 to linkid changes from current value to newcost*/
/* You can leave this routine empty if you're an undergrad. If you want */
/* to use this routine, you'll need to change the value of the LINKCHANGE */
/* constant definition in prog3.c from 0 to 1 */
	
{
}

