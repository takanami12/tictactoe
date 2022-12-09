/*
Game tic tac toe 3x3

Giao diện game:
             X | O |   
            -----------
               |   |   
            -----------
               |   |     


1.AI engine
    +Tạo giao diện game với bảng và vị trí
    +Biểu diễn trạng thái board[][3]
    +Kiểm tra xem game kết thúc chưa
    +Xác định người chiến thắng hoặc hoà
    +Nước đi hợp lệ
        +Xác định người chơi hiện tại
        +Tính toán nước đi hợp lệ
    +Tính điểm của từng trạng thái
        +Tính điểm trạng thái kết thúc
        +Tính điểm trạng thái trung gian
    +Tính toán nước đi tốt nhất
2.UI (User interface)
    +Chọn X hoặc O
    +Nhập vị trí đánh
    +Phản hồi nếu đó là vị trí hợp lệ
    +Phản hồi kết quả nếu game kết thúc
    +In ra nước đi tại từng thời điểm
    +In ra nước đi của máy tính
*/
#include <iostream>
using namespace std; 

//Khai báo biến AI, player, 3 

#define AI 1 
#define player 2 

//Khai báo biến playermove, AImove

char playermove;
char AImove;

//Hàm tạo bảng

void showBoard(char board[][3]) 
{ 
	cout << "                         " <<  board[0][0] << " " <<  "|" << " " << board[0][1] << " " << "|" << " " <<board[0][2] << endl;   
	cout << "                        " << "-----------"<< endl; 
	cout << "                         " <<  board[1][0] << " " <<  "|" << " " << board[1][1] << " " << "|" << " " <<board[1][2] << endl;   
	cout << "                        " << "-----------"<< endl; 
	cout << "                         " <<  board[2][0] << " " <<  "|" << " " << board[2][1] << " " << "|" << " " <<board[2][2] << endl;   
} 

//Hàm chỉ ra vị trí với số tương ứng trên bảng

void showInstructions() 
{ 
    cout << endl << "Choose a cell numbered from 1 to 9 as below and play" << endl << endl; 
	cout << "                         " << "1 | 2 | 3 "<< endl; 
	cout << "                        " << "-----------"<< endl; 
	cout << "                         " << "4 | 5 | 6 "<< endl; 
	cout << "                        " << "-----------"<< endl; 
	cout << "                         " << "7 | 8 | 9 "<< endl; 
} 

//Hàm khởi tạo giá trị trắng cho từng vị trí trong bảng

void initialise(char board[][3]) 
{	
	for (int i=0; i<3; i++) 
	{ 
		for (int j=0; j<3; j++) 
			board[i][j] = ' '; 
	} 
} 

//Hàm xác định người chiến thắng

void declareWinner(int whoseTurn) 
{ 
	if (whoseTurn == AI) 
		cout << "AI has won!"<< endl;
	else
		cout << "You have won!" << endl;
} 

//Hàm xác định điều kiện chiến thắng qua hàng

bool rowCrossed(char board[][3]) 
{ 
	for (int i=0; i<3; i++) 
	{ 
		if (board[i][0] == board[i][1] && 
			board[i][1] == board[i][2] && 
			board[i][0] != ' ') 
			return (true); 
	} 
	return(false); 
} 

//Hàm xác định điều kiện chiến thắng qua cột

bool columnCrossed(char board[][3]) 
{ 
	for (int i=0; i<3; i++) 
	{ 
		if (board[0][i] == board[1][i] && 
			board[1][i] == board[2][i] && 
			board[0][i] != ' ') 
			return (true); 
	} 
	return(false); 
} 
 
//Hàm xác định điều kiện chiến thắng qua đường chéo

bool diagonalCrossed(char board[][3]) 
{ 
	if (board[0][0] == board[1][1] && 
		board[1][1] == board[2][2] && 
		board[0][0] != ' ') 
		return(true); 
		
	if (board[0][2] == board[1][1] && 
		board[1][1] == board[2][0] && 
		board[0][2] != ' ') 
		return(true); 

	return(false); 
} 

//Hàm xác định xem game kết thúc hay chưa

bool gameOver(char board[][3]) 
{ 
	return(rowCrossed(board) || columnCrossed(board) || diagonalCrossed(board) ); 
}

//Hàm tính toán bằng thuật toán minimax

int minimax(char board[][3], int depth, bool isAI)
{
	int score = 0;
	int bestScore = 0;
	if (gameOver(board) == true)
	{
		if (isAI == true) //Nếu AI thắng thì điểm là -1
			return -1;
		if (isAI == false) // Nếu AI thua thì điểm là 1
			return +1;
	}
	else
	{
		if(depth < 9)
		{
			if(isAI == true)
			{
				bestScore = -999;
				for(int i=0; i<3; i++)
				{
					for(int j=0; j<3; j++)
					{
						if (board[i][j] == ' ')
						{
							board[i][j] = AImove;
							score = minimax(board, depth + 1, false);
							board[i][j] = ' '; 
							if(score > bestScore)
							{
								bestScore = score; 
							}
						}
					}
				}
				return bestScore;
			}
			else
			{
				bestScore = 999;
				for (int i = 0; i < 3; i++)
				{
					for (int j = 0; j < 3; j++)
					{
						if (board[i][j] == ' ')
						{
							board[i][j] = playermove;
							score = minimax(board, depth + 1, true);
							board[i][j] = ' '; 
							if (score < bestScore)
							{
								bestScore = score;
							}
						}
					}
				}
				return bestScore;
			}
		}
		else
		{
			return 0;
		}
	}
}

//Hàm tìm ra nước đi tốt nhất dựa trên minimax

int bestMove(char board[][3], int moveIndex)
{
	int x = -1, y = -1;
	int score = 0, bestScore = -999;
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			if (board[i][j] == ' ')
			{
				board[i][j] = AImove;
				score = minimax(board, moveIndex+1, false);
				board[i][j] = ' ';
				if(score > bestScore)
				{
					bestScore = score;
					x = i;
					y = j;
				}
			}
		}
	}
	return x*3+y;
}

//Hàm chạy trò chơi

void playTicTacToe(int whoseTurn) 
{ 
	char board[3][3]; 
	int moveIndex = 0, x = 0, y = 0;

	initialise(board);
	showInstructions(); 
	
	while (gameOver(board) == false && moveIndex != 3*3) 
	{ 
		int n;
		if (whoseTurn == AI) 
		{
			n = bestMove(board, moveIndex);
			x = n / 3;
			y = n % 3;
			board[x][y] = AImove; 
            cout << endl << "AI has put a "<< AImove << " " << "in cell " << n+1<< endl << endl;
			showBoard(board);
			moveIndex ++; 
			whoseTurn = player;
		} 
		
		else if (whoseTurn == player) 
		{
            cout << endl << "You can insert in the following positions : ";
			for(int i=0; i<3; i++)
				for (int j = 0; j < 3; j++)
					if (board[i][j] == ' ')
                        cout << (i*3 + j) + 1;
            cout << endl << endl << "Enter the position = ";
            cin >> n; // Nhập vào vị trí muốn đi
			n--; // Để tạo ra phần nguyên và phần dư đúng với vị trí của mảng
			x = n / 3;
			y = n % 3; 
			if(board[x][y] == ' ' && n<9 && n>=0)
			{
				board[x][y] = playermove; 
                cout << endl << "You has put a "<< playermove<< " " << "in cell " << n+1<< endl << endl;
				showBoard(board); 
				moveIndex ++; 
				whoseTurn = AI;
			}
			else if(board[x][y] != ' ' && n<9 && n>=0)
			{
                cout << endl << "Position is occupied, select any one place from the available places" << endl << endl;
			}
			else if(n<0 || n>8) 
			{
				cout << "Invalid position" <<endl;
			}
		} 
	} 

	if (gameOver(board) == false && moveIndex == 3 * 3) 
		cout << "It's a draw" << endl; 
	else
	{ 
		if (whoseTurn == AI) 
			whoseTurn = player; 
		else if (whoseTurn == player) 
			whoseTurn = AI; 
		
		declareWinner(whoseTurn); 
	} 
} 

int main() 
{   
	cout << endl << "-------------------------------------------------------------------"<< endl << endl;
	cout << "           " << "Tic-Tac-Toe"<< endl <<endl;
	cout << "-------------------------------------------------------------------"<< endl << endl;
	char cont;
	do {
		char choice;
	 	cout << "Do you want to start first(y/n): "; //Hỏi người chơi có muốn chơi trước không
	 	cin >> choice;

		if(choice=='n') //Người chơi không chơi trước
		{
			AImove = 'X';
			playermove = 'O';
			playTicTacToe(AI);
		}
		else if(choice=='y') //Người chơi chơi trước
		{
			playermove = 'X';
			AImove = 'O';
			playTicTacToe(player);
		}
		else
		{
			cout << "Invalid position" << endl; 
		} 
		cout << "Do you want to quit(y/n): "; // Hỏi xem người chơi muốn thoát không
       	cin >> cont;
	} while(cont=='n'); 
	return (0); 
} 
