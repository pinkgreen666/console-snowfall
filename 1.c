#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int area[25][240];

/*
0 - ' '; 1 - '-'; 2 - '|'; 3 - '/'; 4 - '\'; 5 - '^'; 6 - '*'; 7 - 'o'; 8 - '.'; 9 - '#'
*/

void createArea() {
    
    for(int i = 0; i < 25; i++) {
        for(int j = 0; j < 240; j++)
            area[i][j] = 0;
    }
    
    for(int i = 0; i < 240; i++) {
        area[0][i] = 1;
        area[24][i] = 1;
    }
}

//  house
void house() {
    //  walls
    for(int i = 23; i > 15; i--) {
        area[i][90] = 2;
        area[i][110] = 2;
    }
    
    //  floor and ceiling
    for(int i = 90; i < 111; i++) {
        area[15][i] = 1;
        area[24][i] = 1;
    }
    
    //  window
    for(int i = 20; i > 17; i--) {
        area[i][98] = 2;
        area[i][102] = 2;
    }
    for(int i = 98; i < 103; i++) {
        area[17][i] = 1;
        area[21][i] = 1;
    }
    
    //  roof
    for(int i = 90, j = 15; i < 101; i++, j--) {
        area[j][i] = 3;
    }
    for(int i = 110, j = 15; i > 100; i--, j--) {
        area[j][i] = 4;
    }
    area[5][100] = 5;
}

//  trees
void tree() {
    for(int i = 23; i > 19; i--) {
        area[i][130] = 2;
        area[i][131] = 2;
    }
    for(int i = 23; i > 17; i--) {
        area[i][140] = 2;
        area[i][141] = 2;
    }
    
    area[22][129] = 3;
    area[22][128] = 3;
    
    area[22][132] = 4;
    area[22][133] = 4;
    
    area[19][130] = 3;
    area[19][131] = 4;
    
    for(int i = 21; i > 19; i--) {
        area[i][129] = 3;
        area[i][132] = 4;
    }
    
    area[22][139] = 3;
    area[22][138] = 3;
    area[22][137] = 3;
    
    area[22][142] = 4;
    area[22][143] = 4;
    area[22][144] = 4;
    
    area[18][139] = 3;
    area[18][142] = 4;
    
    area[17][140] = 3;
    area[17][141] = 4;
    
    for(int i = 21; i > 18; i--) {
        area[i][139] = 3;
        area[i][138] = 3;
        
        area[i][142] = 4;
        area[i][143] = 4;
    }
    
}

//  snow generation
void snow() {
	int snow[100];
	for(int i = 0; i < 100; i++) {
	    snow[i] = 0;
	}
	snow[0] = 6;
	snow[1] = 7;
	snow[2] = 8;
	for(int i = 0; i < 240; i++) {
		area[1][i] = snow[rand() % 100];
	}
}

//  without wind
void snowfallWithoutWind() {
	for(int i = 23; i > 0; i--) {
		for(int j = 1; j < 240; j++) {
			if(area[i][j] == 6 || area[i][j] == 7 || area[i][j] == 8) {
				if(area[i+1][j] == 0) {
					area[i+1][j] = area[i][j];
					area[i][j] = 0;
				}
				
				//  interaction with objects
				//  '/', '\'
				if(area[i+1][j] == 3 && area[i+1][j-1] == 0) {
					area[i+1][j-1] = area[i][j];
					area[i][j] = 0;
				}
				if(area[i+1][j] == 4 && area[i+1][j+1] == 0) {
					area[i+1][j+1] = area[i][j];
					area[i][j] = 0;
				}

				//  '^'
				if(area[i+1][j] == 5 && (area[i+1][j+1] == 0 || area[i+1][j-1] == 0)) {
				    if(rand()%2 == 1) {
				        area[i+1][j+1] = area[i][j];
				        area[i][j] = 0;
				    }
				    else {
				        area[i+1][j-1] = area[i][j];
				        area[i][j] = 0;
				    }
				}
		    }
	    }
    }
}

//  right wind
void snowfallRightWind() {
    for(int i = 23; i > 0; i--) {
		for(int j = 1; j < 240; j++) {
			if(area[i][j] == 6 || area[i][j] == 7 || area[i][j] == 8) {
                if(area[i+1][j+1] == 0 && area[i+1][j] == 0) {
                    area[i+1][j+1] = area[i][j];
                    area[i][j] = 0;
                }
                
                //  interaction with objects
                //  '/', '\'
                if(area[i+1][j] == 3 && area[i][j+1] != 2) {
                    area[i][j-1] = area[i][j];
                    area[i][j] = 0;
                }
                if(area[i+1][j] == 5 && area[i][j+1] != 2) {
                    area[i][j+1] = area[i][j];
                    area[i][j] = 0;
                }
                
                //  '*', 'o', '.'
                if((area[i+1][j] == 6 || area[i+1][j] == 7 || area[i+1][j] == 8) && area[i+1][j-1] == 0 && area[i+1][j+1] == 0 && area[i][j-1] != 2) {
                    int r = 1 + rand() % 1;
                    switch(r) {
                        case 1:
                            area[i+1][j-1] = area[i][j];
                            area[i][j] = 0;
                            break;
                        case 2:
                            area[i+1][j+1] = area[i][j];
                            area[i][j] = 0;
                            break;
                    }
                }
                
                //  '^'
                if(area[i+1][j] == 5 && area[i+1][j-1] == 0 && area[i+1][j+1] == 0) {
                    int r = 1 + rand() % 1;
                    switch(r) {
                        case 1:
                            area[i+1][j-1] = area[i][j];
                            area[i][j] = 0;
                            break;
                        case 2:
                            area[i+1][j+1] = area[i][j];
                            area[i][j] = 0;
                            break;
                    }
                }
		    }
	    }
    }
}

//  left wind
void snowfallLeftWind() {
    for(int i = 23; i > 0; i--) {
		for(int j = 1; j < 240; j++) {
			if(area[i][j] == 6 || area[i][j] == 7 || area[i][j] == 8) {
                if(area[i+1][j-1] == 0 && area[i+1][j] == 0) {
                    area[i+1][j-1] = area[i][j];
                    area[i][j] = 0;
                }
                
                //  interaction with objects
                //  '/', '\'
                if(area[i+1][j] == 3 && area[i+2][j] == 3) {
                    area[i][j-1] = area[i][j];
                    area[i][j] = 0;
                }
                if(area[i+1][j] == 4 && area[i][j+1] != 2) {
                    area[i][j+1] = area[i][j];
                    area[i][j] = 0;
                }
                
                //  '*', 'o', '.'
                if ((area[i+1][j] == 6 || area[i+1][j] == 7 || area[i+1][j] == 8) && area[i+1][j-1] == 0 && area[i+1][j+1] == 0 && area[i][j-1] != 2) {
                    int r = 1 + rand() % 1;
                    switch (r) {
                        case 1:
                            area[i+1][j-1] = area[i][j];
                            area[i][j] = 0;
                            break;
                        case 2:
                            area[i+1][j+1] = area[i][j];
                            area[i][j] = 0;
                            break;
                    }
                }
                
                //  '^'
                if (area[i+1][j] == 5 && area[i+1][j-1] == 0 && area[i+1][j+1] == 0) {
                    int r = 1 + rand() % 1;
                    switch (r) {
                        case 1:
                            area[i+1][j-1] = area[i][j];
                            area[i][j] = 0;
                            break;
                        case 2:
                            area[i+1][j+1] = area[i][j];
                            area[i][j] = 0;
                            break;
                    }
                }
	        }
        }
	}
}

//  Stack snow
void stackSnow() {
	for(int i = 23; i > 0; i--) {
		for(int j = 1; j < 240; j++) {
			//  '.' + '.' = 'o'
			if(area[i][j] == 8 && area[i-1][j] == 8 && area[i+1][j] != 0) {
				area[i][j] = 7;
				area[i-1][j] = 0;
			}
			
			//  'o' + 'o' = '*'
			if(area[i][j] == 7 && area[i-1][j] == 7 && area[i+1][j] != 0) {
				area[i][j] = 6;
				area[i-1][j] = 0;
			}
			
			//  '.' + 'o' = 'o'
			if(area[i][j] == 7 && area[i-1][j] == 8 && area[i+1][j] != 0) {
				area[i-1][j] = 0;
			}
			
            //  'o' + '.' = 'o'
			if(area[i][j] == 8 && area[i-1][j] == 7 && area[i+1][j] != 0) {
				area[i][j] = 7;
				area[i-1][j] = 0;
			}
			
			//  '.' + '*' = '*'
			if(area[i][j] == 6 && area[i-1][j] == 8 && area[i+1][j] != 0) {
				area[i-1][j] = 0;
			}
			
            //  '*' + '*' = '*'
			if(area[i][j] == 8 && area[i-1][j] == 6 && area[i+1][j] != 0) {
				area[i][j] = 6;
				area[i-1][j] = 0;
			}
			
			//  'o' + '*' = '*'
			if(area[i][j] == 6 && area[i-1][j] == 7 && area[i+1][j] != 0) {
				area[i-1][j] = 0;
			}
			
			//  '*' + 'o' = '*'
			if(area[i][j] == 7 && area[i-1][j] == 6 && area[i+1][j] != 0) {
				area[i][j] = 6;
				area[i-1][j] = 0;
			}
			
			//  '*' + '*' + '*' + '*' + '*' = '#' + '*'
			if(area[i][j] == 9) {
				continue;
			}
			else {
				if(area[i][j] == 6 && area[i-1][j] == 6 && area[i-2][j] == 6 && area[i-3][j] == 6 && area[i-4][j] == 6) {
					area[i][j] = 9;
					area[i-4][j] = 0;
					area[i-3][j] = 0;
					area[i-2][j] = 0;
				}
			}
		}
	}
}

//  sun
void sun() {
    area[1][87] = 1;
    area[2][86] = 1;
    area[3][85] = 1;
    area[4][83] = 1;
    area[5][81] = 1;
}

//  snow melting
void spring() {
    for(int i = 0; i < 25; i++) {
        for(int j = 0; j < 240; j++) {
            if((area[i][j] == 6 || area[i][j] == 7 || area[i][j] == 8 || area[i][j] == 9) && (area[i-1][j] == 0 || area[i-1][j] == 1 || area[i-1][j] == 4 || area[i-1][j] == 3)) {
                if(area[i][j] == 9) {
                    area[i][j] = 6;
                }
                else if(area[i][j] == 6) {
                    area[i][j] = 7;
                }
                else if(area[i][j] == 7) {
                    area[i][j] = 8;
                }
                else if(area[i][j] = 8) {
                    area[i][j] = 0;
                }
            }
        }
    }
}

void draw() {
    for(int i = 0; i < 25; i++) {
        for(int j = 80; j < 160; j++) {
            switch(area[i][j]) {
                case 0:
                    printf("%c", ' ');
                    break;
                case 1:
                    printf("%c", '-');
                    break;
                case 2:
                    printf("%c", '|');
                    break;
                case 3:
                    printf("%c", '/');
                    break;
                case 4:
                    printf("%c", '\\');
                    break;
                case 5:
                    printf("%c", '^');
                    break;
                case 6:
                    printf("%c", '*');
                    break;
                case 7:
                    printf("%c", 'o');
                    break;
                case 8:
                    printf("%c", '.');
                    break;
                case 9:
                    printf("%c", '#');
                    break;
            }
        }
        printf("\n");
    }
}

void moveCursor() {
    //  printf("\033[%d;%dH", 0, 0);
    system("cls");
}

int main() {
    srand(time(NULL));
    createArea();
    house();
    tree();
    draw();
    
    int t = 0;
    while(t < 200) {
        snow();
        int windDirection = rand()%3; // 0 - ; 1 - ветер вправо; 2 - ветер влево

        
        switch(windDirection) {
            
            case 0:  //  without wind
                snowfallWithoutWind();
                break;
            case 1:  //  right wind
                snowfallRightWind();
                break;
            case 2:  //  left wind
                snowfallLeftWind();
                break;
        }
        
        stackSnow();
        moveCursor();
        draw();
        usleep(1000);
        t++;
    }
    
    while(t < 300) {
        sun();
        spring();
        moveCursor();
        draw();
        usleep(1000000);
    }
    
    return 0;
}



