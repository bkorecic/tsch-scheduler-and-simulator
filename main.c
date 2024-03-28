/******************************************************************************
 *
 * Copyright (C) 2022-2023 Maxim Integrated Products, Inc. (now owned by
 * Analog Devices, Inc.),
 * Copyright (C) 2023-2024 Analog Devices, Inc.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 ******************************************************************************/

/**
 * @file    main.c
 * @brief   Hello World!
 * @details This example uses the UART to print to a terminal and flashes an
 * LED.
 */

/***** msdk includes *****/
#include "board.h"
#include "led.h"
#include "mxc_delay.h"
#include "mxc_device.h"
#include <stdio.h>
#include <stdlib.h> // malloc, rand
#include <string.h> // memset

/***** tasa includes *****/
#include "src/graphs/graphs.h"
#include "src/tasa/tasa.h"
#include "src/util/list.h"

/***** Definitions *****/

/***** Globals *****/

/***** Functions *****/
Tree_t *init_network(List *nodesList, List *linksList) {

  // create nodes
  Node_t *nodes[MAX_NODES];
  for (int i = 0; i < MAX_NODES; i++) {
    nodes[i] = newNode(i, CONNECTED);
    nodes[i]->q = rand() % 5 + 1;
    ListAppend(nodesList, (void *)nodes[i]);
  }

  // create links (harcoded in links_ids)
  int links_ids[MAX_NODES - 1][2] = {{1, 0}, {2, 0},  {3, 0},  {4, 0},
                                     {5, 1}, {6, 1},  {7, 2},  {8, 3},
                                     {9, 3}, {10, 4}, {11, 5}, {12, 8}};

  for (int i = 0; i < MAX_NODES - 1; i++) {
    Link_t *link =
        newLink(nodes[links_ids[i][0]], nodes[links_ids[i][1]], 0, 0, 0, i);
    ListAppend(linksList, (void *)link);
  }

  // create trees
  Tree_t *trees[MAX_NODES];
  for (int i = 0; i < MAX_NODES; i++) {
    trees[i] = newTree(nodes[i], 0);
  }

  // this could be written more elegant by storing the parents,
  // and iterating through all parents to add subtree

  // child of 0
  ListAppend(&trees[0]->children_list, (void *)nodes[1]);
  ListAppend(&trees[0]->children_list, (void *)nodes[2]);
  ListAppend(&trees[0]->children_list, (void *)nodes[3]);
  ListAppend(&trees[0]->children_list, (void *)nodes[4]);
  // subtrees of 0
  for (int i = 1; i < MAX_NODES; i++) {
    ListAppend(&trees[0]->subtrees_list, (void *)trees[i]);
  }

  // child of 1
  ListAppend(&trees[1]->children_list, (void *)nodes[5]);
  ListAppend(&trees[1]->children_list, (void *)nodes[6]);
  // subtrees of 1
  ListAppend(&trees[1]->subtrees_list, (void *)trees[5]);
  ListAppend(&trees[1]->subtrees_list, (void *)trees[6]);
  ListAppend(&trees[1]->subtrees_list, (void *)trees[11]);

  // child of 2
  ListAppend(&trees[2]->children_list, (void *)nodes[7]);
  // subtrees of 2
  ListAppend(&trees[2]->subtrees_list, (void *)trees[7]);

  // child of 3
  ListAppend(&trees[3]->children_list, (void *)nodes[8]);
  ListAppend(&trees[3]->children_list, (void *)nodes[9]);
  // subtrees of 3
  ListAppend(&trees[3]->subtrees_list, (void *)trees[8]);
  ListAppend(&trees[3]->subtrees_list, (void *)trees[9]);
  ListAppend(&trees[3]->subtrees_list, (void *)trees[12]);

  // child of 4
  ListAppend(&trees[4]->children_list, (void *)nodes[10]);
  // subtrees of 4
  ListAppend(&trees[4]->subtrees_list, (void *)trees[10]);

  // child of 5
  ListAppend(&trees[5]->children_list, (void *)nodes[11]);
  // subtrees of 5
  ListAppend(&trees[5]->subtrees_list, (void *)trees[11]);

  // child of 8
  ListAppend(&trees[5]->children_list, (void *)nodes[12]);
  // subtrees of 8
  ListAppend(&trees[5]->subtrees_list, (void *)trees[12]);

  return trees[0];
}

// *****************************************************************************
int main(void) {
  /* List of nodes */
  List nodesList;
  memset(&nodesList, 0, sizeof(List));
  ListInit(&nodesList);

  /* List of links */
  List linksList;
  memset(&linksList, 0, sizeof(List));
  ListInit(&linksList);

  Tree_t *tree = init_network(&nodesList, &linksList);

  /* Create the interference matrix considering any interference threshold
   */
  bool intMatrix[MAX_NODES][MAX_NODES][NUM_CHANNELS];
  memset(intMatrix, false, MAX_NODES * MAX_NODES * NUM_CHANNELS * sizeof(bool));
  createInterferenceMatrix(intMatrix, &linksList, 1.0);

  /* Create the conflict matrix considering the connectivity, interference and
   * cmsTree */
  bool confMatrix[MAX_NODES][MAX_NODES][NUM_CHANNELS];
  memset(confMatrix, false,
         MAX_NODES * MAX_NODES * NUM_CHANNELS * sizeof(bool));
  createConflictMatrix(NULL, intMatrix, &nodesList, confMatrix, false);

  main_tasa(&nodesList, &linksList, tree, tree->root->id, intMatrix, confMatrix,
            0);

  // iterate through nodes, print timeslots

  for (ListElem *nodeElem = ListFirst(&nodesList); nodeElem != NULL;
       nodeElem = ListNext(&nodesList, nodeElem)) {
    Node_t *node = (Node_t *)nodeElem->obj;
    printf("Timeslots for node %d\n\ttime\tRX\tTX\n", node->id);
    for (ListElem *tsElem = ListFirst(&node->timeslots); tsElem != NULL;
         tsElem = ListNext(&node->timeslots, tsElem)) {
      TimeSlot_t *ts = (TimeSlot_t *)tsElem->obj;
      int rx, tx;
      if(ts->type == TS_RX){
        rx = node->id;
        tx = ts->neighbor->id;
      }
      else{
        rx = ts->neighbor->id;
        rx = node->id;
      }
      printf("\t%d\t%d\t%d\n", ts->time, rx, tx);
    }
  }
}
