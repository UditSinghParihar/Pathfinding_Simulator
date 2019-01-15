
#include<SFML/Graphics.hpp>
#include<SFML/Audio.hpp>
#include<SFML/Window.hpp>
#include<iostream>
#include<functional>        //for std::bind
#include<math.h>        //Astar libraries
#include<float.h>
#include<vector>
#include<set>
#include<string.h>
#include<string>
#include<sstream>
using namespace std;
using namespace sf;
#define num 60      //number of cells in a row
//--------dijkstra--------
vector<pair<int,int>> pathD;        //Shortest pathD
bool sptSet[num][num];      //explored cells
void findmin(float dist[num][num],int& min_x,int& min_y){
    float mini=FLT_MAX;
    for(int i=0;i<num;i++)
        for(int j=0;j<num;j++)
            if(sptSet[i][j]==false && dist[i][j]<mini){
                mini=dist[i][j];
                min_x=i;
                min_y=j;
            }
}
void findpath(pair<int,int> previous[num][num],float dist[num][num],int dest_x,int dest_y,int source_x,int source_y){
    cout<<"\nLength of Dijkstra path is: "<<dist[dest_x][dest_y]<<endl;
    while(previous[dest_x][dest_y].first!=source_x || previous[dest_x][dest_y].second!=source_y){        // both simultaneously equal to source coordinates
        sf::sleep(milliseconds(10));        //delay shortest pathD
        cout<<"go to ->\n("<<previous[dest_x][dest_y].first<<","<<previous[dest_x][dest_y].second<<") ";
        pathD.push_back(make_pair(previous[dest_x][dest_y].first,previous[dest_x][dest_y].second));
        int save_x=dest_x,save_y=dest_y;
        dest_x=previous[save_x][save_y].first;
        dest_y=previous[save_x][save_y].second;
    }
}
void dijkstra(int source_x,int source_y,int dest_x,int dest_y,int grid[num][num]){
    pair<int,int> previous[num][num];
    float dist[num][num];
    for(int i=0;i<num;i++)
        for(int j=0;j<num;j++)
            dist[i][j]=FLT_MAX;
    dist[source_x][source_y]=0.0;
    int found=0;
    for(int i=0;i<num && found==0;i++)
        for(int j=0;j<num && found==0;j++){
            int min_x=0,min_y=0;
            findmin(dist,min_x,min_y);
            sptSet[min_x][min_y]=true;
            if(sptSet[dest_x][dest_y]==true){
                found=1;
                break;
            }
            sf::sleep(milliseconds(1));        //delay exploration
            //north
            if(grid[min_x-1][min_y]==1 && sptSet[min_x-1][min_y]==false && dist[min_x-1][min_y]>dist[min_x][min_y]+1.0){
                dist[min_x-1][min_y]=dist[min_x][min_y]+1.0;
                previous[min_x-1][min_y]=make_pair(min_x,min_y);
            }
            //south
            if(grid[min_x+1][min_y]==1 && sptSet[min_x+1][min_y]==false && dist[min_x+1][min_y]>dist[min_x][min_y]+1.0){
                dist[min_x+1][min_y]=dist[min_x][min_y]+1.0;
                previous[min_x+1][min_y]=make_pair(min_x,min_y);
            }
            //west
            if(grid[min_x][min_y-1]==1 && sptSet[min_x][min_y-1]==false && dist[min_x][min_y-1]>dist[min_x][min_y]+1.0){
                dist[min_x][min_y-1]=dist[min_x][min_y]+1.0;
                previous[min_x][min_y-1]=make_pair(min_x,min_y);
            }
            //east:i,j+1
            if(grid[min_x][min_y+1]==1 && sptSet[min_x][min_y+1]==false && dist[min_x][min_y+1]>dist[min_x][min_y]+1.0){
                dist[min_x][min_y+1]=dist[min_x][min_y]+1.0;
                previous[min_x][min_y+1]=make_pair(min_x,min_y);
            }
            //north-east:i-1,j+1
            if(grid[min_x-1][min_y+1]==1 && sptSet[min_x-1][min_y+1]==false &&
                dist[min_x-1][min_y+1]>dist[min_x][min_y]+sqrt(2) && !(grid[min_x-1][min_y]==0 && grid[min_x][min_y+1]==0)){
                dist[min_x-1][min_y+1]=dist[min_x][min_y]+sqrt(2);
                previous[min_x-1][min_y+1]=make_pair(min_x,min_y);
            }
            //south-east:i+1,j+1
            if(grid[min_x+1][min_y+1]==1 && sptSet[min_x+1][min_y+1]==false &&
                dist[min_x+1][min_y+1]>dist[min_x][min_y]+sqrt(2) && !(grid[min_x+1][min_y]==0 && grid[min_x][min_y+1]==0)){
                dist[min_x+1][min_y+1]=dist[min_x][min_y]+sqrt(2);
                previous[min_x+1][min_y+1]=make_pair(min_x,min_y);
            }
            //south-west:i+1,j-1
            if(grid[min_x+1][min_y-1]==1 && sptSet[min_x+1][min_y-1]==false &&
                dist[min_x+1][min_y-1]>dist[min_x][min_y]+sqrt(2) && !(grid[min_x+1][min_y]==0 && grid[min_x][min_y-1]==0)){
                dist[min_x+1][min_y-1]=dist[min_x][min_y]+sqrt(2);
                previous[min_x+1][min_y-1]=make_pair(min_x,min_y);
            }
            //north-west:i-1,j-1
            if(grid[min_x-1][min_y-1]==1 && sptSet[min_x-1][min_y-1]==false &&
                dist[min_x-1][min_y-1]>dist[min_x][min_y]+sqrt(2) && !(grid[min_x-1][min_y]==0 && grid[min_x][min_y-1]==0)){
                dist[min_x-1][min_y-1]=dist[min_x][min_y]+sqrt(2);
                previous[min_x-1][min_y-1]=make_pair(min_x,min_y);
            }
        }
    findpath(previous,dist,dest_x,dest_y,source_x,source_y);
}
//--------Astar--------
typedef pair<int,int> Pair;
typedef pair<float,pair<int,int>> Ppair;
bool closedList[num][num];
vector<Pair> pathA;
struct cell{
    int parent_x,parent_y;
    float f,g,h;
    cell() : f(FLT_MAX),g(FLT_MAX),h(FLT_MAX),parent_x(-1),parent_y(-1) {};
};
bool isDestination(int row,int col,Pair dest){
    if(row==dest.first && col==dest.second)
        return true;
    else
        return false;
}
float calculateHvalue(int row,int col,Pair dest){
    int dx=abs(dest.first-row);
    int dy=abs(dest.second-col);
    return abs(dx-dy)+sqrt(2)*min(dx,dy);       //Diagonal D=1,D2=sqrt(2)
}
void tracePath(Pair source,Pair dest,cell cellDetails[][num]){
    int i=cellDetails[dest.first][dest.second].parent_x,j=cellDetails[dest.first][dest.second].parent_y;
    while(!(i==source.first && j==source.second)){
        sf::sleep(milliseconds(10));        //delay shortest path
        cout<<i<<","<<j<<" to -> \n";
        pathA.push_back(make_pair(i,j));
        //pathSum=pathSum+cellDetails[i][j].g;
        int temp_i=i;
        int temp_j=j;
        i=cellDetails[temp_i][temp_j].parent_x;     //Solved substitution bug
        j=cellDetails[temp_i][temp_j].parent_y;
    }
    cout<<"\nLength of A* path(g) is: "<<cellDetails[dest.first][dest.second].g<<endl;
}
void Astar(Pair source,Pair dest,int grid[][num]){
    set<Ppair> openList;
    cell cellDetails[num][num];
    int i= source.first,j=source.second;
    cellDetails[i][j].f=0.0;
    cellDetails[i][j].g=0.0;
    cellDetails[i][j].h=0.0;
    cellDetails[i][j].parent_x=i;
    cellDetails[i][j].parent_y=j;
    openList.insert(make_pair(0.0,make_pair(i,j)));
    bool destFound=false;
    while(!openList.empty()){
        Ppair p=*openList.begin();
        openList.erase(openList.begin());
        int i=p.second.first,j=p.second.second;
        closedList[i][j]=true;
        sf::sleep(milliseconds(1));        //delay exploration
        if(isDestination(i,j,dest)==true){
            cout<<"Destination Found\n";
            destFound=true;
            break;      //out of while loop
        }
        // North:i-1,j
        if(grid[i-1][j]==1 && closedList[i-1][j]==false){
            cell successor;
            successor.g=cellDetails[i][j].g+1.0;
            successor.h=calculateHvalue(i-1,j,dest);
            successor.f=successor.g+successor.h;
            successor.parent_x=i;
            successor.parent_y=j;
            if(cellDetails[i-1][j].g>successor.g){        //Not in openList or bigger 'g' in openList
                cellDetails[i-1][j]=successor;
                openList.insert(make_pair(successor.f,make_pair(i-1,j)));
            }
        }
        // East:i,j+1
        if(grid[i][j+1]==1 && closedList[i][j+1]==false){
            cell successor;
            successor.g=cellDetails[i][j].g+1.0;
            successor.h=calculateHvalue(i,j+1,dest);
            successor.f=successor.g+successor.h;
            successor.parent_x=i;
            successor.parent_y=j;
            if(cellDetails[i][j+1].g>successor.g){        //Not in openList or bigger 'g' in openList
                cellDetails[i][j+1]=successor;
                openList.insert(make_pair(successor.f,make_pair(i,j+1)));
            }
        }
        // South:i+1,j
        if(grid[i+1][j]==1 && closedList[i+1][j]==false){
            cell successor;
            successor.g=cellDetails[i][j].g+1.0;
            successor.h=calculateHvalue(i+1,j,dest);
            successor.f=successor.g+successor.h;
            successor.parent_x=i;
            successor.parent_y=j;
            if(cellDetails[i+1][j].g>successor.g){        //Not in openList or bigger 'g' in openList
                cellDetails[i+1][j]=successor;
                openList.insert(make_pair(successor.f,make_pair(i+1,j)));
            }
        }
        // West:i,j-1
        if(grid[i][j-1]==1 && closedList[i][j-1]==false){
            cell successor;
            successor.g=cellDetails[i][j].g+1.0;
            successor.h=calculateHvalue(i,j-1,dest);
            successor.f=successor.g+successor.h;
            successor.parent_x=i;
            successor.parent_y=j;
            if(cellDetails[i][j-1].g>successor.g){        //Not in openList or bigger 'g' in openList
                cellDetails[i][j-1]=successor;
                openList.insert(make_pair(successor.f,make_pair(i,j-1)));
            }
        }
        // North-East:i-1,j+1
        if(grid[i-1][j+1]==1 && closedList[i-1][j+1]==false && !(grid[i-1][j]==0 && grid[i][j+1]==0)){      //not simultaneously blocked
            cell successor;
            successor.g=cellDetails[i][j].g+sqrt(2);
            successor.h=calculateHvalue(i-1,j+1,dest);
            successor.f=successor.g+successor.h;
            successor.parent_x=i;
            successor.parent_y=j;
            if(cellDetails[i-1][j+1].g>successor.g){        //Not in openList or bigger 'g' in openList
                cellDetails[i-1][j+1]=successor;
                openList.insert(make_pair(successor.f,make_pair(i-1,j+1)));
            }
        }
        // South-East:i+1,j+1
        if(grid[i+1][j+1]==1 && closedList[i+1][j+1]==false && !(grid[i+1][j]==0 && grid[i][j+1]==0)){
            cell successor;
            successor.g=cellDetails[i][j].g+sqrt(2);
            successor.h=calculateHvalue(i+1,j+1,dest);
            successor.f=successor.g+successor.h;
            successor.parent_x=i;
            successor.parent_y=j;
            if(cellDetails[i+1][j+1].g>successor.g){        //Not in openList or bigger 'g' in openList
                cellDetails[i+1][j+1]=successor;
                openList.insert(make_pair(successor.f,make_pair(i+1,j+1)));
            }
        }
        // South-West:i+1,j-1
        if(grid[i+1][j-1]==1 && closedList[i+1][j-1]==false && !(grid[i+1][j]==0 && grid[i][j-1]==0)){
            cell successor;
            successor.g=cellDetails[i][j].g+sqrt(2);
            successor.h=calculateHvalue(i+1,j-1,dest);
            successor.f=successor.g+successor.h;
            successor.parent_x=i;
            successor.parent_y=j;
            if(cellDetails[i+1][j-1].g>successor.g){        //Not in openList or bigger 'g' in openList
                cellDetails[i+1][j-1]=successor;
                openList.insert(make_pair(successor.f,make_pair(i+1,j-1)));
            }
        }
        // North-West:i-1,j-1
        if(grid[i-1][j-1]==1 && closedList[i-1][j-1]==false && !(grid[i-1][j]==0 && grid[i][j-1]==0)){
            cell successor;
            successor.g=cellDetails[i][j].g+sqrt(2);
            successor.h=calculateHvalue(i-1,j-1,dest);
            successor.f=successor.g+successor.h;
            successor.parent_x=i;
            successor.parent_y=j;
            if(cellDetails[i-1][j-1].g>successor.g){        //Not in openList or bigger 'g' in openList
                cellDetails[i-1][j-1]=successor;
                openList.insert(make_pair(successor.f,make_pair(i-1,j-1)));
            }
        }

    }
    if(destFound==false)
        cout<<"Destination cell not found.\n";
    else
        tracePath(source,dest,cellDetails);
}
//--------main()--------
int main(){
    int filled[num][num];       //whether cell is colored
    int grid[60][60];       //map with obstacle
    for(int i=0;i<60;i++)
        for(int j=0;j<60;j++){
            if(i==0||i==59||j==0||j==59)        //walls
                grid[i][j]=0;
            else
                grid[i][j]=1;
        }
     for(int i=0;i<num;i++)
        for(int j=0;j<num;j++){
            sptSet[i][j]=false;     //dijkstra all unexplored
            filled[i][j]=0;     //all uncolored
        }
    memset(closedList,false,sizeof(closedList));        //Astar all unexplored
    int source_x=2,source_y=2,dest_x=50,dest_y=56;      //Origin(2,3)->Goal(50,56)
    Thread threadD(std::bind(&dijkstra,source_x,source_y,dest_x,dest_y,grid));
    Thread threadA(std::bind(&Astar,make_pair(source_x,source_y),make_pair(dest_x,dest_y),grid));
    RenderWindow window(VideoMode(800,600),"Grid");
    // Music
    // sf::Music music;
    // sf::Music music2;
    // if(!music.openFromFile("music.ogg"))
    //     cout<<"Music loading failed!\n";
    // if(!music2.openFromFile("move.ogg"))
    //     cout<<"Music move loading failed!\n";
    // // Text
    sf::Font font;
    font.loadFromFile("arial.ttf");
    sf::Text text1("DIJKSTRA",font,15);
    sf::Text text2("A*",font,24);
    sf::Text lengthD(" ",font,24);
    sf::Text lengthA(" ",font,24);
    // text1.setFillColor(Color::Black);
    // text2.setFillColor(Color::Black);
    // lengthD.setFillColor(Color::Black);
    // lengthA.setFillColor(Color::Black);
    // Shapes
    RectangleShape buttonStartD(Vector2f(75,25));       //button dijkstra
    buttonStartD.setFillColor(Color::Green);
    RectangleShape buttonStartA(Vector2f(75,25));       //button Astar
    buttonStartA.setFillColor(Color::Magenta);
    RectangleShape displayD(Vector2f(75,25));       //Dijkstra display
    displayD.setFillColor(Color::White);
    RectangleShape displayA(Vector2f(75,25));       //Astar display
    displayA.setFillColor(Color::White);
    RectangleShape rectangle(Vector2f(10,10));      //default box :White
    rectangle.setFillColor(Color::White);
    RectangleShape brectangle(Vector2f(10,10));     //Black box
    brectangle.setFillColor(Color::Black);
    RectangleShape grectangle(Vector2f(10,10));     //Green
    grectangle.setFillColor(Color::Green);
    grectangle.setOutlineThickness(2);
    grectangle.setOutlineColor(Color::Red);
    RectangleShape mrectangle(Vector2f(10,10));     //Magenta
    mrectangle.setFillColor(Color::Magenta);
    mrectangle.setOutlineThickness(2);
    mrectangle.setOutlineColor(Color::Red);
    RectangleShape blueRectangle(Vector2f(10,10));
    blueRectangle.setFillColor(Color::Blue);
    blueRectangle.setOutlineThickness(2);
    blueRectangle.setOutlineColor(Color::Red);
    RectangleShape rrectangle(Vector2f(10,10));
    rrectangle.setFillColor(Color::Red);
    rrectangle.setOutlineThickness(2);
    rrectangle.setOutlineColor(Color::Red);
    RectangleShape yrectangle(Vector2f(10,10));
    yrectangle.setFillColor(Color::Yellow);
    // Display
    while(window.isOpen()){
        Event event;
        while(window.pollEvent(event)){
            if(event.type==Event::Closed)
                window.close();
            if(event.type==Event::KeyPressed&& event.key.code==Keyboard::Space)
                window.close();
            if(event.type==Event::MouseButtonPressed&&event.mouseButton.button==Mouse::Left){
                int X=event.mouseButton.x;
                int Y=event.mouseButton.y;
                int row=Y/10;       //Reversed notion of row & column
                int col=X/10;
                if(grid[row][col]==0&&row<60&&col<60)
                    grid[row][col]=1;
                else if(row<60&&col<60)
                    grid[row][col]=0;
                cout<<"Cell "<<row<<" , "<<col<<" state is: "<<grid[row][col]<<endl;
                if(X>600&&X<675&&Y>0&&Y<25){
                    threadD.launch();
                    // music.play();
                }
                if(X>600&&X<675&&Y>75&&Y<100){
                    threadA.launch();
                    // music2.play();
                }
            }
        }
        window.clear();
        buttonStartD.setPosition(600,0);
        window.draw(buttonStartD);      //Dijkstra launch
        buttonStartA.setPosition(600,75);
        window.draw(buttonStartA);      //Astar launch
        displayD.setPosition(725,0);        //Dijkstra length Background
        window.draw(displayD);
        displayA.setPosition(725,75);
        window.draw(displayA);
        text1.setPosition(600,0);       //Dijkstra text
        text2.setPosition(630,75);
        lengthD.setPosition(725,0);     //Display Dijkstra length
        lengthA.setPosition(725,75);
        window.draw(text1);
        window.draw(text2);
        stringstream ss1,ss2;
        ss1<<pathD.size();       //int2string
        lengthD.setString(ss1.str());
        ss2<<pathA.size();
        lengthA.setString(ss2.str());
        window.draw(lengthD);
        window.draw(lengthA);
        if(!pathA.empty()){
            for(int i=0;i<pathA.size();i++){
                mrectangle.setPosition(pathA[i].second*10,pathA[i].first*10);     //Reversed notion of row & column
                window.draw(mrectangle);        //final pathA
                filled[pathA[i].first][pathA[i].second]=1;
            }
        }
        if(!pathD.empty()){
            for(int i=0;i<pathD.size();i++){
                grectangle.setPosition(pathD[i].second*10,pathD[i].first*10);     //Reversed notion of row & column
                window.draw(grectangle);        //final pathD
                filled[pathD[i].first][pathD[i].second]=1;
            }
        }
        blueRectangle.setPosition(source_y*10,source_x*10);
        window.draw(blueRectangle);     //source
        filled[source_x][source_y]=1;
        rrectangle.setPosition(dest_y*10,dest_x*10);
        window.draw(rrectangle);        //destination
        filled[dest_x][dest_y]=1;
        for(int i=0;i<=590 ;i+=10)
            for(int j=0;j<=590;j+=10){
                if(grid[i/10][j/10]==0){
                    brectangle.setOutlineThickness(2);
                    brectangle.setOutlineColor(Color::Red);
                    brectangle.setPosition(j,i);
                    window.draw(brectangle);        //User's obstacle
                }
                if(sptSet[i/10][j/10]==true && filled[i/10][j/10]==0){
                    yrectangle.setOutlineThickness(2);
                    yrectangle.setOutlineColor(Color::Red);
                    yrectangle.setPosition(j,i);
                    window.draw(yrectangle);        // Explored Cells by dijkstra
                }
                if(closedList[i/10][j/10]==true && filled[i/10][j/10]==0){
                    yrectangle.setOutlineThickness(2);
                    yrectangle.setOutlineColor(Color::Red);
                    yrectangle.setPosition(j,i);
                    window.draw(yrectangle);        // Explored  Cells by A*
                }
                if(grid[i/10][j/10]==1 && sptSet[i/10][j/10]==false && closedList[i/10][j/10]==false && filled[i/10][j/10]==0){     //not in dijkstra & A*
                    rectangle.setOutlineThickness(2);
                    rectangle.setOutlineColor(Color::Red);
                    rectangle.setPosition(j,i);
                    window.draw(rectangle);     //default white cells
                }
            }
        window.display();
    }
    return 0;
}

