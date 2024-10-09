#include<stdio.h>
#include<stdlib.h>
#include<conio.h>

//using 1d array
#define HEIGHT 15
#define WIDTH 80

int flag=0,score=0,gameOver=0;

typedef struct{
    int x;
    int y;
}Fruit;

typedef struct{
    int x;
    int y;
}loc;

typedef struct{
    loc body[100];
    int length;
    int level;
}Snake;

void gameInfo(char name[])
{
    printf("\nWelcome %s in game",name);
    printf("\n\n********************Instructions***********************");
    printf("\n\n1. This game consits  of 3 levels");
    printf("\n2. To win a level you need to achieve a score of 100");
    printf("\n3. In 1st level you are allowed to pass through the boundaries");
    printf("\n4. Use the following keys to navigate the snake:");
    printf("\n   - Press 'W' to move Up");
    printf("\n   - Press 'S' to move Down");
    printf("\n   - Press 'A' to move Left");
    printf("\n   - Press 'D' to move Right");
    printf("\n\n*******************************************************");
    printf("\n\nGood luck and have fun!");
    printf("\n\nPress any key to continue");
    printf("\n\nFor exit press X/x");
    char ch = getch();
    if(ch == 'X' || ch == 'x') 
	{
        gameOver = 1;
    }
    score = 0;
}

void setUp(Snake *snake,Fruit *fruit)
{
    snake->body[0].x = HEIGHT/2;   //snake Position
    snake->body[0].y = WIDTH/2;
    snake->length = 1;              //set snake length
    snake->level = 1;               //set level

    //set fruit position
    do{
        fruit->x = rand() % (HEIGHT - 2) + 1;
    } while (fruit->x == 0);

    do{
        fruit->y = rand() % (WIDTH - 2) + 1;
    } while (fruit->y == 0);
}

void draw(Snake *snake,Fruit *fruit)
{
    //to draw snake boundary and snake body
    system("cls");
    for(int i=0; i<=HEIGHT; i++)
    {
        for(int j=0; j<=WIDTH; j++)
        {
            if(i==0 || i==HEIGHT || j==0 || j==WIDTH)
              printf("#");
            else
            {
                int snakePart = 0;
                for(int v=0; v<snake->length; v++)
                {
                    if(snake->body[v].x == i && snake->body[v].y == j)
                    {
                        if(v==0)
                        {
                            printf("@");
                        }
                        else{
                            if(snake->level > 1)
                                printf("o");
                        }
                        snakePart = 1;
                        break; 
                    }
                }
                if(!snakePart)
                {
                    if(fruit->x == i && fruit->y == j)
                        printf("*");  
                    else
                        printf(" ");    
                }
            }
        }
        printf("\n");
    }
    printf("Score: %d\n",score);
    printf("Level: %d\n",snake->level);
    printf("\nEnter X to exit the game");
}

void input()
{
    if(kbhit())                                       //if key press it returns 1 otherwise 0
    {
        switch(getch())
        {
            case 'a':
              if(flag!=4)
                flag = 1;
              break;

            case 's':
             if(flag!=3)
                flag = 2;
             break;

            case 'w':
            if(flag!=2)
                flag = 3;
             break;

            case 'd':
            if(flag!=1)
                flag = 4;
            break;

            case 'x':
              system("cls");
              printf("\nYou Exit the game");
              printf("\nScore: %d\n",score);
              gameOver = 1;      
              break;
        }
    }
}

void run(Snake *snake,Fruit *fruit)
{
    //Move the snake
    for(int i=snake->length-1; i>0; i--)
    {
        snake->body[i] = snake->body[i-1];
    }

    //Moving the snake head
    if(flag == 1)
     snake->body[0].y--;
    else if(flag == 2)
     snake->body[0].x++;
    else if(flag == 3)
     snake->body[0].x--;
    else if(flag == 4)
     snake->body[0].y++;  

    //to eat the fruit
    if(snake->body[0].x == fruit->x && snake->body[0].y == fruit->y)
    {
        snake->length++;
        score++;
        do{
            fruit->x = rand() % (HEIGHT - 2) + 1;
        } while (fruit->x == 0);

        do{
            fruit->y = rand() % (WIDTH - 2) + 1;
        } while (fruit->y == 0);
    } 

    //to pass through from the boundary for level 1 and level 2
    if(snake->level < 3)
    {
       if (snake->body[0].x <= 0)
            snake->body[0].x = HEIGHT - 1;
        if (snake->body[0].x >= HEIGHT)
            snake->body[0].x = 1;
        if (snake->body[0].y <= 0)
            snake->body[0].y = WIDTH - 1;
        if (snake->body[0].y >= WIDTH)
            snake->body[0].y = 1;
    }
    
    //for level 3
    else
    {
        char ch;
        //if snake touches the boundary
        if(snake->body[0].x <= 0 || snake->body[0].x>= HEIGHT || snake->body[0].y <= 0 || snake->body[0].y >= WIDTH)
        {
            getch();
            printf("\nGame Over!!!!   You touched the boundary");
            printf("\nScore: %d",score);
            printf("\nIf you want to play again then press Y/N");
            ch = getch();
            if(ch == 'n' || ch == 'N')
              gameOver = 1;
            else{
                gameOver = 0;
                score = 0;
                main();        
            }
        }

        //If snake hits your ownself
        for(int i=1; i<snake->length; i++)
        {
            if(snake->level == 3 && snake->body[0].x == snake->body[i].x && snake->body[0].y == snake->body[i].y)
            {
                getch();
                printf("Game Over!!!!   You hit your own tail");
                printf("\nIf you want to play again then press Y/N");
                char ch = getch();
                if(ch == 'n' || ch == 'N'){
                    gameOver = 1;
                }
                else{
                    gameOver = 0;
                    score = 0;
                    main();
                }
            }
        }

        //if he/she wins the game
        if(score >= 10)
        {
            system("cls");
            printf("\nYou win");
            printf("\nYour Score is: %d",score);
            printf("Do you want to restart(Y/N)");
            ch = getch();
            if(ch == 'n' || ch == 'N')
              gameOver = 1;
            else{
                gameOver = 0;
                score = 0;
                main();  
            }
        }
    }

    //to win the level 1
    if(score >= 3 && snake->level == 1)
    {
        system("cls");
        snake->level = 2;
        snake->length = 2;
        score = 0;
        printf("\nYou win level 1");
        printf("\nPress Any key to continue: ");
        printf("\n\nFor exit press X/x");
        char ch = getch();
        if(ch == 'X' || ch == 'x') 
	    {
            gameOver = 0;
        }
    }

    //to win level 2
    if(score  >= 5 && snake->level == 2)
    {
        system("cls");
        snake->level = 3;
        // snake->length = 2;
        // score = 0;
        printf("\nYou win level 2");
        printf("\nPress any key to continue: ");
        printf("\n\nFor exit press X/x");
        char ch = getch();
        if(ch == 'X' || ch == 'x') 
	    {
            gameOver = 0;
        }
    }
}

int main()
{   Snake snake;
    Fruit fruit;
    char name[50];

    system("cls");
    printf("\nEnter your name: ");
    scanf("%s",name);

    system("cls");
    gameInfo(name);
    setUp(&snake,&fruit);

    while(!gameOver){
    draw(&snake,&fruit);
    input();
    run(&snake,&fruit);
    for(int i=0; i<3000; i++){
      for(int j=0; j<150000; j++){
      }
    }
   }
}