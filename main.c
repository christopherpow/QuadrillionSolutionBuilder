// QuadrillionSolutionBuilder.cpp
//
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define NUM_BOARD_PIECES         4
#define NUM_BOARDPIECE_SIDES     2
#define NUM_BOARDPIECE_ORIENTS   4
#define NUM_BOARDPIECE_LOCATIONS 4

unsigned int board_pieces[NUM_BOARD_PIECES][NUM_BOARDPIECE_SIDES][NUM_BOARDPIECE_ORIENTS] =
{
   {
      {
         0x90000000, 0x10000010, 0x00000090, 0x80000080
      },
      {
         0x00100010, 0x000000a0, 0x80008000, 0x50000000
      }
   },
   {
      {
         0x40000000, 0x00100000, 0x00000020, 0x00008000
      },
      {
         0x20000000, 0x00001000, 0x00000040, 0x00800000
      }
   },
   {
      {
         0x60000000, 0x00101000, 0x00000060, 0x00808000
      },
      {
         0x00400080, 0x80200000, 0x10002000, 0x00004010
      }
   },
   {
      {
         0x10008000, 0x40000010, 0x00100080, 0x80000020
      },
      {
         0x00002080, 0x80004000, 0x10400000, 0x00200010
      }
   }
};

unsigned long long boards[98304];

#define NUM_GAME_PIECES  12
#define NUM_GAMEPIECE_ORIENTS 4
#define NUM_GAMEPIECE_SIDES   2

typedef struct
{
   unsigned int data;
   int          xextent;
   int          yextent;
} T_GAMEPIECE;

T_GAMEPIECE piece_data [ NUM_GAME_PIECES ] [ NUM_GAMEPIECE_SIDES ] [ NUM_GAMEPIECE_ORIENTS ] =
{
   // Piece 0 [orange] (side 0, 0 degree orientation shown)
   {
      // Side 0
      // .x.. x... .xx. .x..
      // .xx. xxx. xx.. xxx.
      // xx.. .x.. .x.. ..x.
      // .... .... .... ....
      {
         { 0x4060c000, 3, 3 }, // 0 degrees
         { 0x80e04000, 3, 3 }, // 90 degrees
         { 0x60c04000, 3, 3 }, // 180 degrees
         { 0x40e02000, 3, 3 }  // 270 degrees
      },
      // Side 1
      // .x.. .x.. xx.. ..x.
      // xx.. xxx. .xx. xxx.
      // .xx. x... .x.. .x..
      // .... .... .... ....
      {
         { 0x40c06000, 3, 3 }, // 0 degrees
         { 0x40e08000, 3, 3 }, // 90 degrees
         { 0xc0604000, 3, 3 }, // 180 degrees
         { 0x20e04000, 3, 3 }  // 270 degrees
      }
   },
   // Piece 1 [light red] (side 0, 0 degree orientation shown)
   {
      // Side 0
      // ...x x... xxxx xx..
      // xxxx x... x... .x..
      // .... x... .... .x..
      // .... xx.. .... .x..
      {
         { 0x10f00000, 4, 2 }, // 0 degrees
         { 0x808080c0, 2, 4 }, // 90 degrees
         { 0xf0800000, 4, 2 }, // 180 degrees
         { 0xc0404040, 2, 4 }  // 270 degrees
      },
      // Side 1
      // x... xx.. xxxx .x..
      // xxxx x... ...x .x..
      // .... x... .... .x..
      // .... x... .... xx..
      {
         { 0x80f00000, 4, 2 }, // 0 degrees
         { 0xc0808080, 2, 4 }, // 90 degrees
         { 0xf0100000, 4, 2 }, // 180 degrees
         { 0x404040c0, 2, 4 }  // 270 degrees
      }
   },
   // Piece 2 [turquoise] (side 0, 0 degree orientation shown)
   {
      // Side 0
      // xxx. ..x. .x.. x...
      // .x.. xxx. .x.. xxx.
      // .x.. ..x. xxx. x...
      // .... .... .... ....
      {
         { 0xe0404000, 3, 3 }, // 0 degrees
         { 0x20e02000, 3, 3 }, // 90 degrees
         { 0x4040e000, 3, 3 }, // 180 degrees
         { 0x80e08000, 3, 3 }  // 270 degrees
      },
      // Side 1
      // Side-symmetric
      {
         { 0x00000000, 8, 8 }, // 0 degrees
         { 0x00000000, 8, 8 }, // 90 degrees
         { 0x00000000, 8, 8 }, // 180 degrees
         { 0x00000000, 8, 8 }  // 270 degrees
      }
   },
   // Piece 3 [purple] (side 0, 0 degree orientation shown)
   {
      // Side 0
      // .xx. xx.. ..x. x...
      // xx.. .xx. .xx. xx..
      // x... ..x. xx.. .xx.
      // .... .... .... ....
      {
         { 0x60c08000, 3, 3 }, // 0 degrees
         { 0xc0602000, 3, 3 }, // 90 degrees
         { 0x2060c000, 3, 3 }, // 180 degrees
         { 0x80c06000, 3, 3 }  // 270 degrees
      },
      // Side 1
      // Side-symmetric
      {
         { 0x00000000, 8, 8 }, // 0 degrees
         { 0x00000000, 8, 8 }, // 90 degrees
         { 0x00000000, 8, 8 }, // 180 degrees
         { 0x00000000, 8, 8 }  // 270 degrees
      }
   },
   // Piece 4 [light blue] (side 0, 0 degree orientation shown)
   {
      // Side 0
      // x... xxx. xxx. ..x.
      // x... x... ..x. ..x.
      // xxx. x... ..x. xxx.
      // .... .... .... ....
      {
         { 0x8080e000, 3, 3 }, // 0 degrees
         { 0xe0808000, 3, 3 }, // 90 degrees
         { 0xe0202000, 3, 3 }, // 180 degrees
         { 0x2020e000, 3, 3 }  // 270 degrees
      },
      // Side 1
      // Side-symmetric
      {
         { 0x00000000, 8, 8 }, // 0 degrees
         { 0x00000000, 8, 8 }, // 90 degrees
         { 0x00000000, 8, 8 }, // 180 degrees
         { 0x00000000, 8, 8 }  // 270 degrees
      }
   },
   // Piece 5 [dark red] (side 0, 0 degree orientation shown)
   {
      // Side 0
      // .x.. xx..
      // xx.. .xx.
      // x... ....
      // .... ....
      {
         { 0x40c08000, 2, 3 }, // 0 degrees
         { 0xc0600000, 3, 2 }, // 90 degrees
         { 0x00000000, 8, 8 }, // 180 degrees
         { 0x00000000, 8, 8 }  // 270 degrees
      },
      // Side 1
      // x... .xx.
      // xx.. xx..
      // .x.. ....
      // .... ....
      {
         { 0x80c04000, 2, 3 }, // 0 degrees
         { 0x60c00000, 3, 2 }, // 90 degrees
         { 0x00000000, 8, 8 }, // 180 degrees
         { 0x00000000, 8, 8 }  // 270 degrees
      }
   },
   // Piece 6 [dark blue] (side 0, 0 degree orientation shown)
   {
      // Side 0
      // xx.. ..x. .... ....
      // .x.. xxx. .... ....
      // .xx. x... .... ....
      // .... .... .... ....
      {
         { 0xc0406000, 3, 3 }, // 0 degrees
         { 0x20e08000, 3, 3 }, // 90 degrees
         { 0x00000000, 8, 8 }, // 180 degrees
         { 0x00000000, 8, 8 }  // 270 degrees
      },
      // Side 1
      // .xx. x... .... ....
      // .x.. xxx. .... ....
      // xx.. ..x. .... ....
      // .... .... .... ....
      {
         { 0x6040c000, 3, 3 }, // 0 degrees
         { 0x80e02000, 3, 3 }, // 90 degrees
         { 0x00000000, 8, 8 }, // 180 degrees
         { 0x00000000, 8, 8 }  // 270 degrees
      }
   },

   // Piece 7 [light light blue] (side 0, 0 degree orientation shown)
   {
      // Side 0
      // xx.. .x.. x... xx..
      // .x.. xx.. xx.. x...
      // .... .... .... ....
      // .... .... .... ....
      {
         { 0xc0400000, 2, 2 }, // 0 degrees
         { 0x40c00000, 2, 2 }, // 90 degrees
         { 0x80c00000, 2, 2 }, // 180 degrees
         { 0xc0800000, 2, 2 }  // 270 degrees
      },
      // Side 1
      // Side-symmetric
      {
         { 0x00000000, 8, 8 }, // 0 degrees
         { 0x00000000, 8, 8 }, // 90 degrees
         { 0x00000000, 8, 8 }, // 180 degrees
         { 0x00000000, 8, 8 }  // 270 degrees
      }
   },
   // Piece 8 [yellow] (side 0, 0 degree orientation shown)
   {
      // Side 0
      // x... xxxx .x.. .x..
      // xx.. ..x. .x.. xxxx
      // x... .... xx.. ....
      // x... .... .x.. ....
      {
         { 0x80c08080, 2, 4 }, // 0 degrees
         { 0xf0200000, 4, 2 }, // 90 degrees
         { 0x4040c040, 2, 4 }, // 180 degrees
         { 0x40f00000, 4, 2 }  // 270 degrees
      },
      // Side 1
      // .x.. ..x. x... xxxx
      // xx.. xxxx x... .x..
      // .x.. .... xx.. ....
      // .x.. .... x... ....
      {
         { 0x40c04040, 2, 4 }, // 0 degrees
         { 0x20f00000, 4, 2 }, // 90 degrees
         { 0x8080c080, 2, 4 }, // 180 degrees
         { 0xf0400000, 4, 2 }  // 270 degrees
      }
   },
   // Piece 9 [cyan]
   {
      // Side 0
      // x... xxx. xx.. .xx.
      // xx.. xx.. xx.. xxx.
      // xx.. .... .x.. ....
      // .... .... .... ....
      {
         { 0x80c0c000, 2, 3 }, // 0 degrees
         { 0xe0c00000, 3, 2 }, // 90 degrees
         { 0xc0c04000, 2, 3 }, // 180 degrees
         { 0x60e00000, 3, 2 }  // 270 degrees
      },
      // Side 1
      // .x.. xx.. xx.. xxx.
      // xx.. xxx. xx.. .xx.
      // xx.. .... x... ....
      // .... .... .... ....
      {
         { 0x40c0c000, 2, 3 }, // 0 degrees
         { 0xc0e00000, 3, 2 }, // 90 degrees
         { 0xc0c08000, 2, 3 }, // 180 degrees
         { 0xe0600000, 3, 2 }  // 270 degrees
      }
   },
   // Piece 10 [green]
   {
      // Side 0
      // xx.. xxx. xx.. x.x.
      // x... x.x. .x.. xxx.
      // xx.. .... xx.. ....
      // .... .... .... ....
      {
         { 0xc080c000, 2, 3 }, // 0 degrees
         { 0xe0a00000, 3, 2 }, // 90 degrees
         { 0xc040c000, 2, 3 }, // 180 degrees
         { 0xa0e00000, 3, 2 }  // 270 degrees
      },
      // Side 1
      // Side-symmetric
      {
         { 0x00000000, 8, 8 }, // 0 degrees
         { 0x00000000, 8, 8 }, // 90 degrees
         { 0x00000000, 8, 8 }, // 180 degrees
         { 0x00000000, 8, 8 }  // 270 degrees
      }
   },
   // Piece 11 [pink]
   {
      // Side 0
      // xxx. .x.. xx.. .x..
      // ..xx .x.. .xxx xx..
      // .... xx.. .... x...
      // .... x... .... x...
      {
         { 0xe0300000, 4, 2 }, // 0 degrees
         { 0x4040c080, 2, 4 }, // 90 degrees
         { 0xc0700000, 4, 2 }, // 180 degrees
         { 0x40c08080, 2, 4 }  // 270 degrees
      },
      // Side 1
      // .xxx x... ..xx x...
      // xx.. xx.. xxx. x...
      // .... .x.. .... xx..
      // .... .x.. .... .x..
      {
         { 0x70c00000, 4, 2 }, // 0 degrees
         { 0x80c04040, 2, 4 }, // 90 degrees
         { 0x30e00000, 4, 2 }, // 180 degrees
         { 0x8080c040, 2, 4 }  // 270 degrees
      }
   }
};

typedef struct
{
   unsigned long long data;
   unsigned long long _data;
   int      side;
   int      orient;
   int      x;
   int      y;
} T_MOVE;

T_MOVE move_data [ NUM_GAME_PIECES ] [ 392 ]; // 49 is max pos (392 is 49 * orients * sides)
int      move_counts [ NUM_GAME_PIECES ];

void build_move_variants()
{
   unsigned long long mask;
   int bit;
   int piece, side, orient, x, y;

   printf("Building move variations...\n" );
   memset ( move_data, 0, sizeof(move_data) );
   for ( piece = 0; piece < NUM_GAME_PIECES; piece++ )
   {
      move_counts [ piece ] = 0;
      for ( side = 0; side < NUM_GAMEPIECE_SIDES; side++ )
      {
         for ( orient = 0; orient < NUM_GAMEPIECE_ORIENTS; orient++ )
         {
            if ( (piece_data[piece][side][orient].xextent < 8) &&
                (piece_data[piece][side][orient].yextent < 8) )
            {
               for ( y = 0; y <= 8-piece_data[piece][side][orient].yextent; y++ )
               {
                  for ( x = 0; x <= 8-piece_data[piece][side][orient].xextent; x++ )
                  {
                     move_data [ piece ] [ move_counts[piece] ].data =
                     ((((unsigned long long)piece_data[piece][side][orient].data)<<32)>>((y*8)+x));
                     move_data [ piece ] [ move_counts[piece] ].side = side;
                     move_data [ piece ] [ move_counts[piece] ].orient = orient;
                     move_data [ piece ] [ move_counts[piece] ].x = x;
                     move_data [ piece ] [ move_counts[piece] ].y = y;

                     mask = 0x0000000000000000;
                     for ( bit = 0; bit < 64-((y*8)+x); bit++ )
                     {
                        mask |= (((unsigned long long)1)<<bit);
                     }
                     move_data [ piece ] [ move_counts[piece] ].data &= mask;
                     move_data [ piece ] [ move_counts[piece] ]._data = ~move_data [ piece ] [ move_counts[piece] ].data;

                     move_counts [ piece ]++;
                  }
               }
            }
         }
      }
      printf ( "%d:%03d ", piece, move_counts[piece] );
   }
   printf ( "done!\n" );
}

unsigned long long rotate_board(unsigned long long board)
{
   int x, y, _x, _y;
   unsigned long long newBoard = 0x0000000000000000ull;
   unsigned long long bit;

#define BIT 0x8000000000000000ull

   // Consider all squares one by one
   for (int x = 0; x < 8 / 2; x++)
   {
      // Consider elements in group of 4 in
      // current square
      for (int y = x; y < 8-x-1; y++)
      {
         // move values from right to top
         // mat[x][y] = mat[y][N-1-x];
         bit = (board&(BIT>>(((y)*8)+(7-x))))?BIT:0;
         newBoard |= (bit>>(((x)*8)+(y)));

         // move values from bottom to right
         // mat[y][N-1-x] = mat[N-1-x][N-1-y];
         bit = (board&(BIT>>(((7-x)*8)+(7-y))))?BIT:0;
         newBoard |= (bit>>(((y)*8)+(7-x)));

         // move values from left to bottom
         // mat[N-1-x][N-1-y] = mat[N-1-y][x];
         bit = (board&(BIT>>(((7-y)*8)+(x))))?BIT:0;
         newBoard |= (bit>>(((7-x)*8)+(7-y)));

         // assign temp to left
         // mat[N-1-y][x] = mat[x][y];
         bit = !!(board&(BIT>>(((x)*8)+(y))))?BIT:0;
         newBoard |= (bit>>(((7-y)*8)+(x)));
      }
   }

   return newBoard;
}

int solve_board(unsigned long long board)
{
   unsigned long long board_data = board;
   int i0 = 0, i1 = 0, i2 = 0, i3 = 0,
       i4 = 0, i5 = 0, i6 = 0, i7 = 0,
       i8 = 0, i9 = 0, i10 = 0, i11 = 0;
   int solutions = 0;
   int sol;
   FILE* fp;
   char filename[64];
   T_MOVE *md0, *md1, *md2, *md3, *md4, *md5, *md6, *md7, *md8, *md9, *md10, *md11;

   sprintf(filename,"sols_%llx.txt",board);
   fp = fopen(filename,"w");

   if ( fp )
   {
      printf ( "Calculating solutions for board %llx\n",board );
      md0 = move_data[0];
      for ( i0 = 0 ; i0 < move_counts[0]; i0++ )
      {
         board_data = board;
         if ( (board_data&(md0->data)) == 0 )
         {
            board_data |= md0->data;
            md1 = move_data[1];
            for ( i1 = 0 ; i1 < move_counts[1]; i1++ )
            {
               if ( (board_data&(md1->data)) == 0 )
               {
                  board_data |= md1->data;
                  md2 = move_data[2];
                  for ( i2 = 0 ; i2 < move_counts[2]; i2++ )
                  {
                     if ( (board_data&(md2->data)) == 0 )
                     {
                        board_data |= md2->data;
                        md3 = move_data[3];
                        for ( i3 = 0 ; i3 < move_counts[3]; i3++ )
                        {
                           if ( (board_data&(md3->data)) == 0 )
                           {
                              board_data |= md3->data;
                              md4 = move_data[4];
                              for ( i4 = 0 ; i4 < move_counts[4]; i4++ )
                              {
                                 if ( (board_data&(md4->data)) == 0 )
                                 {
                                    board_data |= md4->data;
                                    md5 = move_data[5];
                                    for ( i5 = 0 ; i5 < move_counts[5]; i5++ )
                                    {
                                       if ( (board_data&(md5->data)) == 0 )
                                       {
                                          board_data |= md5->data;
                                          md6 = move_data[6];
                                          for ( i6 = 0 ; i6 < move_counts[6]; i6++ )
                                          {
                                             if ( (board_data&(md6->data)) == 0 )
                                             {
                                                board_data |= md6->data;
                                                md7 = move_data[7];
                                                for ( i7 = 0 ; i7 < move_counts[7]; i7++ )
                                                {
                                                   if ( (board_data&(md7->data)) == 0 )
                                                   {
                                                      board_data |= md7->data;
                                                      md8 = move_data[8];
                                                      for ( i8 = 0 ; i8 < move_counts[8]; i8++ )
                                                      {
                                                         if ( (board_data&(md8->data)) == 0 )
                                                         {
                                                            board_data |= md8->data;
                                                            md9 = move_data[9];
                                                            for ( i9 = 0 ; i9 < move_counts[9]; i9++ )
                                                            {
                                                               if ( (board_data&(md9->data)) == 0 )
                                                               {
                                                                  board_data |= md9->data;
                                                                  md10 = move_data[10];
                                                                  for ( i10 = 0 ; i10 < move_counts[10]; i10++ )
                                                                  {
                                                                     if ( (board_data&(md10->data)) == 0 )
                                                                     {
                                                                        board_data |= md10->data;
                                                                        md11 = move_data[11];
                                                                        for ( i11 = 0 ; i11 < move_counts[11]; i11++ )
                                                                        {
                                                                           if ( (board_data&(md11->data)) == 0 )
                                                                           {
                                                                              board_data |= md11->data;
                                                                              if ( board_data == 0xffffffffffffffff )
                                                                              {
                                                                                 fprintf ( fp, "%d,"
                                                                                               "%d,%d,%d,%d,"
                                                                                               "%d,%d,%d,%d,"
                                                                                               "%d,%d,%d,%d,"
                                                                                               "%d,%d,%d,%d,"
                                                                                               "%d,%d,%d,%d,"
                                                                                               "%d,%d,%d,%d,"
                                                                                               "%d,%d,%d,%d,"
                                                                                               "%d,%d,%d,%d,"
                                                                                               "%d,%d,%d,%d,"
                                                                                             "%d,%d,%d,%d,"
                                                                                             "%d,%d,%d,%d,"
                                                                                               "%d,%d,%d,%d\n",
                                                                                          solutions,
                                                                                          md0->side,md0->orient,md0->x,md0->y,
                                                                                          md1->side,md1->orient,md1->x,md1->y,
                                                                                          md2->side,md2->orient,md2->x,md2->y,
                                                                                          md3->side,md3->orient,md3->x,md3->y,
                                                                                          md4->side,md4->orient,md4->x,md4->y,
                                                                                          md5->side,md5->orient,md5->x,md5->y,
                                                                                          md6->side,md6->orient,md6->x,md6->y,
                                                                                          md7->side,md7->orient,md7->x,md7->y,
                                                                                          md8->side,md8->orient,md8->x,md8->y,
                                                                                          md9->side,md9->orient,md9->x,md9->y,
                                                                                          md10->side,md10->orient,md10->x,md10->y,
                                                                                          md11->side,md11->orient,md11->x,md11->y);
//                                                                                 printf ( "0:%03d 1:%03d 2:%03d 3:%03d 4:%03d 5:%03d 6:%03d 7:%03d 8:%03d 9:%03d 10:%03d 11:%03d\n",
//                                                                                         i0, i1, i2, i3, i4, i5, i6, i7, i8, i9, i10, i11 );

                                                                                 solutions++;
                                                                              }
                                                                              board_data &= md11->_data;
                                                                           }
                                                                           md11++;
                                                                        }
                                                                        board_data &= md10->_data;
                                                                     }
                                                                     md10++;
                                                                  }
                                                                  board_data &= md9->_data;
                                                               }
                                                               md9++;
                                                            }
                                                            board_data &= md8->_data;
                                                         }
                                                         md8++;
                                                      }
                                                      board_data &= md7->_data;
                                                   }
                                                   md7++;
                                                }
                                                board_data &= md6->_data;
                                             }
                                             md6++;
                                          }
                                          board_data &= md5->_data;
                                       }
                                       md5++;
                                    }
                                    board_data &= md4->_data;
                                 }
                                 md4++;
                              }
                              board_data &= md3->_data;
                           }
                           md3++;
                        }
                        board_data &= md2->_data;
                     }
                     md2++;
                  }
                  board_data &= md1->_data;
               }
               md1++;
            }
         }
         md0++;
      }

      printf ( "\n%d solutions found!\n", solutions );
      fclose(fp);
   }

   return solutions;
}

int create_or_load_board_list()
{
   int p1, p2, p3, p4;
   int s1, s2, s3, s4;
   unsigned char b1;
   int b = 0, c, f;
   unsigned long long board;
   FILE* fp;

   fp = fopen("boards.txt","r");
   if ( fp )
   {
      while (!feof(fp))
      {
         c = fscanf(fp,"%llx\n",&board);
         if ( c == 1 )
         {
            boards[b++] = board;
         }
      }
      fclose(fp);
   }
   else
   {
      fp = fopen("boards.txt","w");

      if ( fp )
      {
         for ( p1 = 0; p1 < NUM_BOARD_PIECES; p1++ )
         {
            for ( p2 = 0; p2 < NUM_BOARD_PIECES; p2++ )
            {
               for ( p3 = 0; p3 < NUM_BOARD_PIECES; p3++ )
               {
                  for ( p4 = 0; p4 < NUM_BOARD_PIECES; p4++ )
                  {
                     b1 = (1<<p1)|(1<<p2)|(1<<p3)|(1<<p4);
                     if ( b1 == 0xF )
                     {
                        for ( s1 = 0; s1 < NUM_BOARDPIECE_SIDES*NUM_BOARDPIECE_ORIENTS; s1++ )
                        {
                           for ( s2 = 0; s2 < NUM_BOARDPIECE_SIDES*NUM_BOARDPIECE_ORIENTS; s2++ )
                           {
                              for ( s3 = 0; s3 < NUM_BOARDPIECE_SIDES*NUM_BOARDPIECE_ORIENTS; s3++ )
                              {
                                 for ( s4 = 0; s4 < NUM_BOARDPIECE_SIDES*NUM_BOARDPIECE_ORIENTS; s4++ )
                                 {
                                    board = ((unsigned long long)(board_pieces[p1][s1>>2][s1&0x3])<<32)
                                    |((unsigned long long)(board_pieces[p2][s2>>2][s2&0x3])<<28)
                                    |((unsigned long long)(board_pieces[p3][s3>>2][s3&0x3])<<0)
                                    |((unsigned long long)(board_pieces[p4][s4>>2][s4&0x3])>>4);

                                    unsigned long long rot1 = rotate_board(board);
                                    unsigned long long rot2 = rotate_board(rot1);
                                    unsigned long long rot3 = rotate_board(rot2);

                                    f = 0;
                                    for ( c = 0; c < b; c++ )
                                    {
                                       if ( (boards[c] == board) ||
                                           (boards[c] == rot1) ||
                                           (boards[c] == rot2) ||
                                           (boards[c] == rot3) )
                                       {
                                          f = 1;
                                          break;
                                       }
                                    }
                                    if ( !f )
                                    {
                                       boards[b++] = board;
                                       fprintf(fp,"%llx\n",board);
                                    }
                                 }
                              }
                           }
                        }
                     }
                  }
               }
            }
         }
         fclose(fp);
      }
   }

   return b;
}

int main(int argc, char* argv[])
{
   int b = create_or_load_board_list();
   int c;

   build_move_variants();

   for ( c = 0; c < b; c++ )
   {
      solve_board(boards[c]);
   }

   return 0;
}

