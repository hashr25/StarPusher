#include <fstream>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

vector<string> mapFill( vector<string> currentMap );
string convertLine( string line );
void floodFill( vector<string>& mapToFill, int x, int y, char convertFrom, char convertTo );
void makeCorners( vector<string>& mapToFill, int mapHeight, int mapWidth, char convertFrom, char convertTo );


int main()
{
    ifstream inputFile;
    inputFile.open( "starPusherLevels.txt" );
    if( inputFile.fail() )
    {
        cout << "Failed to open the file!" << endl;
    }

    else
    {
        ofstream outputFile;
        outputFile.open( "convertedMaps.txt" );

        string line = "";
        int lineCounter = 0;

        int playerX = 0;
        int playerY = 0;

        int numberOfStars = 0;
        vector<int> starX;
        vector<int> starY;

        vector<int> goalX;
        vector<int> goalY;

        int mapWidth = 0;
        int mapHeight = 0;

        vector<string> mapLines;
        vector<string> baseMapLines;

        while( getline( inputFile, line ) )
        {
            ///Finishing Map
            if( lineCounter > 0 && line.size() < 2 )
            {
                ///Make Floors and Corners
                floodFill( baseMapLines, playerX, playerY, ' ', '^' );

                ///Adding in goals
                for( int i = 0; i < goalX.size(); i++ )
                {
                    baseMapLines.at(goalY.at(i)).at(goalX.at(i)) = '.';
                }

                makeCorners( baseMapLines, mapHeight, mapWidth, '#', '%' );

                ///Converts to our format
                for( int i = 0; i < baseMapLines.size(); i++ )
                {
                    mapLines.push_back( convertLine( baseMapLines.at(i) ) );
                }

                ///Fills map to width
                mapLines = mapFill( mapLines );
                mapHeight =  mapLines.size();

                ///Map dimensions
                outputFile << mapWidth << " " << mapHeight << " " << '\n';

                ///Map key
                for( int i = 0; i < mapLines.size(); i++ )
                {
                    outputFile << mapLines.at(i);
                }

                ///Player Location
                outputFile << playerX << " " << playerY << " " << '\n';

                ///Number of Stars
                outputFile << numberOfStars << " " << '\n';

                ///Star Locations
                for( int i = 0; i < starX.size(); i++ )
                {
                    outputFile << starX.at(i) << " " << starY.at(i) << " ";
                }
                outputFile << '\n';

                ///Goal locations
                for( int i = 0; i < goalX.size(); i++ )
                {
                    outputFile << goalX.at(i) << " " << goalY.at(i) << " ";
                }
                outputFile << "\n\n\n";


                ///Cleanup
                numberOfStars = 0;
                starX.clear();
                starY.clear();
                goalX.clear();
                goalY.clear();
                baseMapLines.clear();
                mapLines.clear();
                lineCounter = 0;
                mapHeight = 0;
                mapWidth = 0;
            }

            else if( line.size() < 2 )
            {
                outputFile  << '\n';
            }

            else if( line.at(0) == ';' )
            {
                outputFile << line << '\n';
            }

            ///EACH LINE
            else
            {
                string mapLine;

                if( line.size() > mapWidth )
                {
                    mapWidth = line.size();
                }

                ///INSIDE LINE
                for( int i = 0; i < line.size(); i++ )
                {
                    ///Grass
                    if( line[i] == ' ' )
                    {
                        mapLine.append( " " );
                    }

                    ///Player
                    else if( line[i] == '@' )
                    {
                        mapLine.append( " " );

                        playerX = i;
                        playerY = lineCounter;
                    }

                    ///Player and goal
                    else if( line[i] == '+' )
                    {
                        mapLine.append( " " );
                        goalX.push_back(i);
                        goalY.push_back(lineCounter);
                        playerX = i;
                        playerY = lineCounter;
                    }

                    ///Star
                    else if( line[i] == '$' )
                    {
                        mapLine.append( " " );
                        starX.push_back(i);
                        starY.push_back(lineCounter);
                        numberOfStars++;
                    }

                    ///Star on Goal
                    else if( line[i] == '*' )
                    {
                        mapLine.append( " " );
                        starX.push_back(i);
                        starY.push_back(lineCounter);
                        goalX.push_back(i);
                        goalY.push_back(lineCounter);
                        numberOfStars++;
                    }

                    ///Goal
                    else if( line[i] == '.' )
                    {
                        mapLine.append( " " );
                        goalX.push_back(i);
                        goalY.push_back(lineCounter);
                    }

                    ///Wall
                    else if( line[i] == '#' )
                    {
                        mapLine.append( "#" );
                    }

                    else if( line[i] == '%' )
                    {
                        mapLine.append( "%" );
                    }

                }///INSIDE LINE

                mapLine.append("\n");

                baseMapLines.push_back( mapLine );
                //mapLines.push_back( mapLine );
                lineCounter++;
            }//EACH LINE
        }

        inputFile.close();
        outputFile.close();
    }
}

vector<string> mapFill( vector<string> currentMap )
{
    vector<string> newMap = currentMap;
    int mapWidth = 0;

    ///Find width
    for( int i = 0; i < currentMap.size(); i++ )
    {
        if( mapWidth < currentMap.at(i).size() )
        {
            mapWidth = currentMap.at(i).size();
        }
    }

    for( int i = 0; i < currentMap.size(); i++ )
    {
        if( currentMap.at(i).size() != mapWidth )
        {
            ///Clear \n
            newMap.at(i).erase( newMap.at(i).size()-1 );

            int charactersToAdd = ( mapWidth - currentMap.at(i).size() ) / 3;

            for( int j = 0; j < charactersToAdd; j++ )
            {
                newMap.at(i).append( "12 " );
            }

            newMap.at(i).append( "\n" );
        }
    }

    vector<string> mapCopy = newMap;

    ///Flood Fill
    for( int i = 0; i < mapCopy.size(); i++ )
    {
        for( int j = 0; j < mapCopy.at(i).size(); j++ )
        {

        }
    }

    return newMap;
}

string convertLine( string line )
{
    string mapLine = "";

    ///INSIDE LINE
    for( int i = 0; i < line.size(); i++ )
    {
        if( line.at(i) == ' ' )
        {
            mapLine.append("12 ");
        }

        else if( line.at(i) == '@' )
        {
            mapLine.append("12 ");
            //playerX = i;
            //playerY = lineCounter;
        }

        else if( line.at(i) == '+' )
        {
            mapLine.append("08 ");
            //playerX = i;
            //playerY = lineCounter;
        }

        else if( line.at(i) == '$' )
        {
            mapLine.append("12 ");
            //starX.push_back(i);
            //starY.push_back(lineCounter);
            //numberOfStars++;
        }

        else if( line.at(i) == '*' )
        {
            mapLine.append("07 ");
            //starX.push_back(i);
            //starY.push_back(lineCounter);
            //numberOfStars++;
        }

        else if( line.at(i) == '.' )
        {
            mapLine.append("08 ");
        }

        else if( line.at(i) == '#' )
        {//cout << "Writing Wall" << endl;
            mapLine.append("10 ");
        }

        else if( line.at(i) == '^' )
        {//cout << "Writing floor" << endl;
            mapLine.append( "09 " );
        }

        else if( line.at(i) == '%' )
        {//cout << "Writing corner" << endl;
            mapLine.append( "11 " );
        }
    }///INSIDE LINE

    mapLine.append("\n");

    return mapLine;
}

void floodFill( vector<string>& mapToFill, int x, int y, char convertFrom, char convertTo )
{
    if( mapToFill.at(y).at(x) == convertFrom )
    {
        mapToFill.at(y).at(x) = convertTo;
    }

    ///Call Right
    if( ( x < ( mapToFill.at(y).size() - 1 ) ) && ( mapToFill.at(y).at(x+1) == convertFrom ) )
    {
        floodFill( mapToFill, x+1, y, convertFrom, convertTo );
    }

    ///Call Left
    if( ( x > 0 ) && ( mapToFill.at(y).at(x-1) == convertFrom ) )
    {
        floodFill( mapToFill, x-1, y, convertFrom, convertTo );
    }

    ///Call Up
    if( ( y > 0 ) && ( mapToFill.at(y-1).at(x) == convertFrom ) )
    {
        floodFill( mapToFill, x, y-1, convertFrom, convertTo );
    }

    ///Call Down
    if( ( y < ( mapToFill.size() - 1 ) ) && ( mapToFill.at(y+1).at(x) == convertFrom ) )
    {
        floodFill( mapToFill, x, y+1, convertFrom, convertTo );
    }
}

void makeCorners( vector<string>& mapToFill, int mapHeight, int mapWidth, char convertFrom, char convertTo )
{
    for( int mapY = 0; mapY < mapToFill.size(); mapY++ )
    {

        for( int mapX = 0; mapX < mapToFill.at(mapY).size(); mapX++ )
        {

            if( mapToFill.at(mapY).at(mapX) == convertFrom )
            {

                int numberOfWallsBeside = 0;
                int numberOfWallsAbove = 0;

                if( mapY+1 < mapToFill.size() && mapX < mapToFill.at(mapY+1).size() )
                {
                    if( mapToFill.at(mapY+1).at(mapX) == convertFrom ||
                        mapToFill.at(mapY+1).at(mapX) == convertTo    )
                    {
                        numberOfWallsAbove++;
                    }
                }

                if( mapY-1 > 0 && mapX < mapToFill.at(mapY-1).size())
                {
                    if( mapToFill.at(mapY-1).at(mapX) == convertFrom ||
                        mapToFill.at(mapY-1).at(mapX) == convertTo    )
                    {
                        numberOfWallsAbove++;
                    }
                }

                if( mapX+1 < mapToFill.at(mapY).size() )
                {
                    if( mapToFill.at(mapY).at(mapX+1) == convertFrom ||
                        mapToFill.at(mapY).at(mapX+1) == convertTo    )
                    {
                        numberOfWallsBeside++;
                    }
                }

                if( mapX-1 > 0 )
                {
                    if( mapToFill.at(mapY).at(mapX-1) == convertFrom ||
                        mapToFill.at(mapY).at(mapX-1) == convertTo    )
                    {
                        numberOfWallsBeside++;
                    }
                }

                if( numberOfWallsAbove > 0 && numberOfWallsBeside > 0 )
                {//cout << "making Corner" << endl;
                    mapToFill.at(mapY).at(mapX) = convertTo;
                }
            }
        }
    }
}
