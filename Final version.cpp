#include < iostream > 
#include < fstream > 
#include < math.h > 
#include < vector > 
#include < string.h > 
#include < ctime > 
#include < cstdlib >

using namespace std;

int ex;
float t;
float f;
int start_time, end_time;

//the structure to identify the location in terms of row and column index
struct ans {
  int row;
  int col;
}
a;

struct node {
  int p;
  int n;
  int points;
  bool max_player;
  int depth;
  char input_mat[26][26];
  int no_of_children;
  node * children[500];
  node * parent;
  bool is_leaf;
  ans loc;
  int alpha;
  int beta;
};

node * bestnode = new node;
node * minmax = new node;

node * funct(ans loc, node * t) //takes in the matrix and specific location, returns the score and matrix after playing for that location 
{

  node * curr = new node;

  curr - > n = t - > n;
  for (int l = 0; l < t - > n; l++)
    for (int o = 0; o < t - > n; o++)
      curr - > input_mat[l][o] = t - > input_mat[l][o];
  curr - > points = t - > points;
  curr - > depth = t - > depth;
  curr - > max_player = t - > max_player;
  

  static int count = 0;
  static char num;

  if (curr - > input_mat[loc.row][loc.col] != '*') 
  {
    num = curr - > input_mat[loc.row][loc.col];
    count = count - count;
  }
  curr - > input_mat[loc.row][loc.col] = '*';

  if (loc.row < curr - > n and curr - > input_mat[loc.row + 1][loc.col] == num) 
  {
    count++;
    curr - > input_mat[loc.row + 1][loc.col] = '*';
    ans l;
    l.row = loc.row + 1;
    l.col = loc.col;
    curr = funct(l, curr);
  }

  if (loc.col < curr - > n and curr - > input_mat[loc.row][loc.col + 1] == num) 
  {
    count++;
    curr - > input_mat[loc.row][loc.col + 1] = '*';
    ans l;
    l.row = loc.row;
    l.col = loc.col + 1;
    curr = funct(l, curr);
  }

  if (loc.row >= 0 and curr - > input_mat[loc.row - 1][loc.col] == num) 
  {
    count++;
    curr - > input_mat[loc.row - 1][loc.col] = '*';
    ans l;
    l.row = loc.row - 1;
    l.col = loc.col;
    curr = funct(l, curr);
  }

  if (loc.col >= 0 and curr - > input_mat[loc.row][loc.col - 1] == num) 
  {
    count++;
    curr - > input_mat[loc.row][loc.col - 1] = '*';
    ans l;
    l.row = loc.row;
    l.col = loc.col - 1;
    curr = funct(l, curr);
  }
  if (curr - > max_player)
    curr - > points = (count + 1) * (count + 1);
  else
    curr - > points = -(count + 1) * (count + 1);

  return curr;
}

node * alphabeta(node * m) 
{

  node * result;
  int i, j, l;

  clock_t end;
  end = clock();
  end_time = end;

  float fa = ((float)(end_time - start_time)) / CLOCKS_PER_SEC;
  

  if (fa > t - 1)

  {
    ofstream myWriteFile;
    myWriteFile.open("output.txt");

    
    char alpha = (char) bestnode - > loc.col + 65;
    myWriteFile << alpha << bestnode - > loc.row + 1 << "\n";

    for (i = 0; i < bestnode - > n; i++) {
      for (j = 0; j < bestnode - > n; j++) {
        myWriteFile << bestnode - > input_mat[i][j];
      }
      myWriteFile << "\n";
    }

    myWriteFile.close();

    exit(0);

  }

  if (m - > is_leaf or m - > depth == 3) 
  {
    if (m - > max_player)
      m - > alpha = m - > points;
    else
      m - > beta = m - > points;
    return m;
  }

  if (m - > max_player) 
  {
    
     
    cout<<"\n root node.. \n";
	for (i = 0; i<m->n; i++)
	{
		for (j = 0; j<m->n; j++)
		{
			
			cout<<m->input_mat[i][j];
        }
		cout << endl;
	}
 cout<<"\n val"<<m->points<<"\n alpha"<<m->alpha<<"\n beta"<<m->beta<<"\n";
		
 
 
 
 
 
     
 cout<<"\n no of children"<<m->no_of_children<<"\n";  
    result = new node;
    for (i = 0; i < m - > no_of_children; i++) {
      

      m - > children[i] - > alpha = m - > alpha;
      m - > children[i] - > beta = m - > beta;

      
      node * temp = new node;
      temp = alphabeta(m - > children[i]);
      
 for (l = 0; l<temp->n; l++)
	{
		for (j = 0; j<temp->n; j++)
		{
			
			cout<<temp->input_mat[l][j];
        }
		cout << endl;
	}
 cout<<"\n value"<<temp->points<<"\n alpha"<<temp->alpha<<"\n beta"<<temp->beta<<"\n";
	


      if (temp - > points > m - > points) {
        m - > points = temp - > points;
        result = m - > children[i];
        
      }
      if (m - > alpha < temp - > points) {
        m - > alpha = temp - > points;

      }
      
      if (m - > beta <= m - > alpha)
        break;
    }
    return result;

  } else {
    
    result = new node;
    for (i = 0; i < m - > no_of_children; i++) {
      

      m - > children[i] - > alpha = m - > alpha;
      m - > children[i] - > beta = m - > beta;

      
      node * temp = alphabeta(m - > children[i]);

      
      if (temp - > points < m - > points) {
        m - > points = temp - > points;
        result = m - > children[i];

        
      }
      
      if (m - > beta > temp - > points) {
        m - > beta = temp - > points;

      }
      
      if (m - > beta <= m - > alpha)
        break;
    }
    return result;

  }
}

void gen_children(node * root) {
  clock_t end;
  end = clock();
  end_time = end;

  f = ((float)(end_time - start_time)) / CLOCKS_PER_SEC;
  

  if (f >= 10) { //cout<<f;
    ofstream myWriteFile;
    myWriteFile.open("output.txt");
    
    char alpha = (char) bestnode - > loc.col + 65;
    myWriteFile << alpha << bestnode - > loc.row + 1 << "\n";

    for (int i = 0; i < bestnode - > n; i++) {
      for (int j = 0; j < bestnode - > n; j++) {
        myWriteFile << bestnode - > input_mat[i][j];
      }
      myWriteFile << "\n";
    }
    myWriteFile.close();

    exit(0);

  }

  int i, j, k;

  root - > alpha = -99999;
  root - > beta = 99999;
  int count = 0;

  for (i = 0; i < root - > n; i++) {
    for (j = 0; j < root - > n; j++)
      if (root - > input_mat[i][j] != '*')
        count++;
  }

  if (count == 0) {
    root - > is_leaf = true;
    return;
  }

  if (root - > depth == 3)
    return;
  else {

    //for generating the child nodes of matrix m
    char test[26][26];

    for (i = 0; i < root - > n; i++)
      for (j = 0; j < root - > n; j++)
        test[i][j] = root - > input_mat[i][j];

    k = 0;

    for (i = 0; i < root - > n; i++) {
      for (j = 0; j < root - > n; j++) {
        if (test[i][j] != '*') {
          ans possible_move;
          possible_move.row = i;
          possible_move.col = j;
          node * temp = new node;
          temp - > n = root - > n;
          temp - > depth = root - > depth;
          temp - > max_player = root - > max_player;
          for (int l = 0; l < root - > n; l++)
            for (int o = 0; o < root - > n; o++)
              temp - > input_mat[l][o] = root - > input_mat[l][o];
          temp - > points = root - > points;

          root - > children[k] = funct(possible_move, temp);
          root - > children[k] - > loc = possible_move;

          root - > children[k] - > parent = root;
          root - > children[k] - > points += root - > points;

          for (int x = 0; x < root - > n; x++) {
            for (int y = 0; y < root - > n; y++) {
              if (root - > children[k] - > input_mat[x][y] == '*')
                test[x][y] = '*';
            }

          }

          for (int x = 0; x < root - > n; x++) {
            for (int y = 0; y < root - > n; y++) {
              here: if (root - > children[k] - > input_mat[x][y] != '*'
                and root - > children[k] - > input_mat[x + 1][y] == '*') {

                root - > children[k] - > input_mat[x + 1][y] = root - > children[k] - > input_mat[x][y];
                root - > children[k] - > input_mat[x][y] = '*';

                if (x - 1 >= 0 or root - > children[k] - > input_mat[x - 1][y] == '*') {
                  x--;
                  goto here;
                }
              }
            }

          }

          k++;
        }

      }
    }

    //till here, next level child nodes genetrated..

    if (root - > max_player)
      root - > points = -999999;
    else
      root - > points = 999999;

    k--;
    int temp_val_of_k;
    temp_val_of_k = k;
    root - > no_of_children = k + 1;

    while (temp_val_of_k >= 0) {
      for (i = 0; i < root - > n; i++) {
        for (j = 0; j < root - > n; j++) {
          if (root - > depth % 2 == 0)
            root - > children[temp_val_of_k] - > max_player = false;
          else
            root - > children[temp_val_of_k] - > max_player = true;
          root - > children[temp_val_of_k] - > depth = root - > depth + 1;

          if (root - > parent == NULL and root - > children[temp_val_of_k] - > points > bestnode - > points)
            bestnode = root - > children[temp_val_of_k];

          
        } 
      } 

      

      temp_val_of_k--;
    }

    while (k >= 0) {

      node * next_node = new node;
      next_node = root - > children[k];

      gen_children(next_node);

      k--;
    }

  }

}

int main() {

  clock_t cl;
  cl = clock();
  start_time = cl;
  node * root = new node;
  int score = 0;
  int i, j;
  char c;
  ifstream myReadFile;
  ofstream myWriteFile;
  myReadFile.open("input.txt");
  myWriteFile.open("output.txt");
  myReadFile >> root - > n;
  myReadFile >> root - > p;
  myReadFile >> t;


  for (i = 0; i < root - > n; i++) {
    for (j = 0; j < root - > n; j++) {
      myReadFile >> c;
      root - > input_mat[i][j] = c;
    }
    cout << endl;
  }

  root - > depth = 0;
  root - > max_player = true;
  root - > points = 0;
  root - > parent = NULL;

  bestnode = root;
  gen_children(root);

  minmax = alphabeta(root);

  char alpha = (char) minmax - > loc.col + 65;
  myWriteFile << alpha << minmax - > loc.row + 1 << "\n";

  for (i = 0; i < root - > n; i++) {
    for (j = 0; j < root - > n; j++) {
      myWriteFile << minmax - > input_mat[i][j];
    }
    myWriteFile << "\n";
  }

  myReadFile.close();
  myWriteFile.close();

  return 0;
}