//
//  os.cpp
//  os
//
//  Created by Malhar Trivedi on 28/01/21.
//

#include <iostream>
#include <bits/stdc++.h>
#include <ctime>
using namespace std;

struct process{
    int bt,at;
    int order;
    int wt=0,tat=0;

};
int no_files = 0;
int no_folders = 0;
bool stat1 = false;
bool stat2 = false;
bool stat3 = false;
bool stat4 = false;

struct file
{
  int file_size;
  string file_name;
  string file_ext;
  char* date_time;
};

struct folder
{
  int t_file_size;
  string folder_name;
  char* date_time;
  list <file> file_list;
  list <folder> folder_list;
};

struct inodes
{
  int type = -1; // -1 if not allocated. 0 if direct block. 1 if indirect block.
  char* date_time;
  struct folder* next_fol = NULL;
  struct file* next_fil = NULL;
};

inodes inode_array[10];

// Done
char* get_dt()
{
  time_t now = time(0);
  char* dt = ctime(&now);
  return (dt);
}

// Done
void show_file(list <file> file_list)
{
  list <file> :: iterator it;
  for(it = file_list.begin(); it !=file_list.end(); ++it)
  {
    cout<<(*it).file_name<<endl;
  }
  cout<<endl;
}

// Done
void show_folder(list <folder> fol_list)
{
  list <folder> :: iterator it;
  for(it = fol_list.begin(); it !=fol_list.end(); ++it)
  {
    cout<<(*it).folder_name<<endl;
  }
  cout<<endl;
}

// Done
bool add_file()
{
  string file_name;
  string ext;
  int file_size;
  bool out = false;

  cout<<"Enter the file name : "<<endl;
  cin>>file_name;
  cout<<"Enter file size : "<<endl;
  cin>>file_size;
  cout<<"Enter file extension : "<<endl;
  cin>>ext;

  for(int i=0; i<10; i++)
  {
    if(inode_array[i].type == -1)
    {
      ++no_files;
      inode_array[i].date_time = get_dt();
      file *new_file = new file;
      new_file->file_name = file_name;
      new_file->file_size = file_size;
      new_file->file_ext = ext;
      new_file->date_time = get_dt();
      inode_array[i].next_fil = new_file;
      inode_array[i].type = 0;
      out = true;
      break;
    }
  }
  return out;
}

// Done
bool add_folder()
{
      string fold_name;
      bool out = false;

      cout<<"Enter the name of the folder"<<endl;
      cin>>fold_name;
      for(int i=0; i<10; i++)
      {
          if(inode_array[i].type == -1)
          {
              ++no_folders;
              inode_array[i].date_time = get_dt();
              folder *new_folder = new folder;
              new_folder->t_file_size = 0;
              new_folder->folder_name = fold_name;
              new_folder->date_time = get_dt();
              inode_array[i].next_fol = new_folder;
              inode_array[i].type = 1;
              out = true;
              break;
          }
      }
      return out;
}

// Done
bool delete_file()
{
    string name_file;
    bool out = false;

    cout<<"Enter the name of the file"<<endl;
    cin>>name_file;

    for(int i=0; i<10; i++)
    {
        if((inode_array[i].type == 0)&&((inode_array[i].next_fil)->file_name == name_file))
        {
            --no_files;
            inode_array[i].date_time = get_dt();
            delete(inode_array[i].next_fil);
            inode_array[i].next_fil = NULL;
            inode_array[i].type = -1;
            out = true;
            break;
        }
    }
    return out;
}

// Done
bool delete_folder()
{
    string name_folder;
    bool out = false;

    cout<<"Enter the name of the file"<<endl;
    cin>>name_folder;

    for(int i=0; i<10; i++)
    {
        if((inode_array[i].type == 1)&&((inode_array[i].next_fol)->folder_name == name_folder))
        {
            --no_folders;
            inode_array[i].date_time = get_dt();
            delete(inode_array[i].next_fol);
            inode_array[i].next_fol = NULL;
            inode_array[i].type = -1;
            out = true;
            break;
        }
    }
    return out;
}

// Done
bool rec_add_fil_fol(folder &f, string fil_name, string fol_name, int fs, string ext)
{
    if(f.folder_name == fol_name)
    {
        ++no_files;
        file *new_file = new file;
        new_file->date_time = get_dt();
        new_file->file_ext = ext;
        new_file->file_name = fil_name;
        new_file->file_size = fs;
        f.t_file_size += fs;
        (f.file_list).push_back(*new_file);
        stat2 = true;
    }
    else if(f.folder_name != fol_name)
    {
        list <folder> :: iterator it;
        for(it = (f.folder_list).begin(); it !=(f.folder_list).end(); ++it)
        {
            rec_add_fil_fol(*it, fil_name, fol_name, fs, ext);
        }
    }
    return stat2;
}

// Done
bool rec_add_fol_fol(folder &f, string p_fol, string c_fol)
{
    if(f.folder_name == p_fol)
    {
        ++no_folders;
        folder *new_folder = new folder;
        new_folder->date_time = get_dt();
        new_folder->folder_name = c_fol;
        new_folder->t_file_size = 0;
        (f.folder_list).push_back(*new_folder);
        stat1 = true;
    }
    else if(f.folder_name != p_fol)
    {
        list <folder> :: iterator it;
        for(it = (f.folder_list).begin(); it !=(f.folder_list).end(); it++)
        {
            rec_add_fol_fol(*it, p_fol, c_fol);
        }
    }
    return stat1;
}

// Done
bool rec_del_fil_fol(folder &f, string fil_name, string fol_name)
{
    if(f.folder_name == fol_name)
    {
        list <file> :: iterator fd;
        for(fd = (f.file_list).begin(); fd != (f.file_list).end(); fd++)
        {
            if((*fd).file_name == fil_name)
            {
                --no_files;
                (f.file_list).erase(fd);
                stat3 = true;
                break;
            }
        }
    }
    else if(f.folder_name != fol_name)
    {
        list <folder> :: iterator it;
        for(it = (f.folder_list).begin(); it !=(f.folder_list).end(); it++)
        {
            rec_del_fil_fol(*it, fil_name, fol_name);
        }
    }
    return stat3;
}

// Done
bool rec_del_fol_fol(folder &f, string p_fol, string c_fol)
{
    if(f.folder_name == p_fol)
    {
        list <folder> :: iterator fd;
        for(fd = (f.folder_list).begin(); fd != (f.folder_list).end(); fd++)
        {
            if((*fd).folder_name == c_fol)
            {
                --no_folders;
                (f.folder_list).erase(fd);
                stat4 = true;
                break;
            }
        }
    }
    else if(f.folder_name != p_fol)
    {
        list <folder> :: iterator it;
        for(it = (f.folder_list).begin(); it !=(f.folder_list).end(); it++)
        {
            rec_del_fol_fol(*it, p_fol, c_fol);
        }
    }
    return stat4;
}

// Done
bool add_f_file()
{
    string name_folder;
    string name_file;
    string name_ext;
    int file_size;
    bool out = false;

    cout<<"Enter the name of the file"<<endl;
    cin>>name_file;
    cout<<"Enter the name of the folder"<<endl;
    cin>>name_folder;
    cout<<"Enter the size of the file"<<endl;
    cin>>file_size;
    cout<<"Enter the file extension"<<endl;
    cin>>name_ext;

    for(int i = 0; i<10; i++)
    {
        if(inode_array[i].type == 1)
        {
            rec_add_fil_fol(*inode_array[i].next_fol, name_file, name_folder, file_size, name_ext);
            if(stat2 == true)
            {
                break;
            }
        }
    }
    return stat2;
}

// Done
bool add_f_folder()
{
    string p_folder;
    string c_folder;

    cout<<"Enter the name of the parent folder"<<endl;
    cin>>p_folder;
    cout<<"Enter the name of the child folder"<<endl;
    cin>>c_folder;

    for(int i = 0; i<10; i++)
    {
        if(inode_array[i].type == 1)
        {
            rec_add_fol_fol(*inode_array[i].next_fol, p_folder, c_folder);
            if(stat1 == true)
            {
                break;
            }
        }
    }
    return stat1;
}

// Done
bool delete_f_file()
{
    string name_folder;
    string name_file;

    cout<<"Enter the name of the folder"<<endl;
    cin>>name_folder;
    cout<<"Enter the name of the file"<<endl;
    cin>>name_file;

    for(int i=0; i<10; i++)
    {
        if(inode_array[i].type == 1)
        {
            rec_del_fil_fol(*inode_array[i].next_fol,name_file, name_folder);
            if(stat3 == true)
            {
                break;
            }
        }
    }
    return stat3;
}

// Done
bool delete_f_folder()
{
    string p_folder;
    string c_folder;

    cout<<"Enter the name of the parent folder"<<endl;
    cin>>p_folder;
    cout<<"Enter the name of the child folder"<<endl;
    cin>>c_folder;

    for(int i=0; i<10; i++)
    {
        if(inode_array[i].type == 1)
        {
            rec_del_fol_fol(*inode_array[i].next_fol, p_folder, c_folder);
            if(stat4 == true)
            {
                break;
            }
        }
    }
    return stat4;
}

bool compare_bt(process p1,process p2){
    return(p1.bt<p2.bt);
}

void SJF(vector<process> p,int n){
    vector<process> rq;
    int i=0,j,k=0,h,total=0;
    float avg;
    for(int o=0;o<n;o++){
        total=total+p[o].bt;
    }
    while(1){
        for(j=0;j<n;j++){
            if(p[j].at==i){
                rq.push_back(p[j]);
            }
        }
        k++;
        sort(rq.begin(),rq.end(),compare_bt);
        cout<<endl;
        rq[0].bt--;
        if(rq.size()>1){
        for(h=1;h<rq.size();h++){
            for(j=0;j<n;j++){
                if(p[j].order==rq[h].order){
                    p[j].wt++;
                }
            }
            rq[h].wt++;
        }
        }
        if(rq[0].bt==0){
            rq.erase(rq.begin());
        }
        if(i==total){break;}
        i++;
    }
     for(i=0;i<n;i++){
        cout<<"Wait Time of process "<<i+1<<" is "<<p[i].wt<<endl;
        avg=avg+p[i].wt;
        p[i].tat=p[i].bt+p[i].wt;
        cout<<"Turn around Time of process "<<i+1<<" is "<<p[i].tat<<endl;
    }
    cout<<"Average waiting time is: "<<avg/n<<endl;
}




void main1(){cout<<"Enter number of processes"<<endl;
    int n;
    cin>>n;
    int i;
    int bt,at;
    vector<process> p;
    for(i=0;i<n;i++){
        cout<<"Enter burst time of process "<<i+1<<endl;
        cin>>bt;
        cout<<"Enter arrival time of process "<<i+1<<endl;
        cin>>at;
        p.push_back(process());
        p[i].bt=bt;
        p[i].at=at;
        p[i].order=i;
    }
    SJF(p,n);}
    int size = 8;
int disk_size = 200;

void CSCAN(int arr[], int head)
{
    int seek_count = 0;
    int distance, cur_track;
    vector<int> left, right;
    vector<int> seek_sequence;

    // appending end values
    // which has to be visited
    // before reversing the direction
    left.push_back(0);
    right.push_back(disk_size - 1);

    // tracks on the left of the
    // head will be serviced when
    // once the head comes back
    // to the beggining (left end).
    for (int i = 0; i < size; i++) {
        if (arr[i] < head)
            left.push_back(arr[i]);
        if (arr[i] > head)
            right.push_back(arr[i]);
    }

    // sorting left and right vectors
    std::sort(left.begin(), left.end());
    std::sort(right.begin(), right.end());

    // first service the requests
    // on the right side of the
    // head.
    for (int i = 0; i < right.size(); i++) {
        cur_track = right[i];
        // appending current track to seek sequence
        seek_sequence.push_back(cur_track);

        // calculate absolute distance
        distance = abs(cur_track - head);

        // increase the total count
        seek_count += distance;

        // accessed track is now new head
        head = cur_track;
    }

    // once reached the right end
    // jump to the beggining.
    head = 0;

    // Now service the requests again
    // which are left.
    for (int i = 0; i < left.size(); i++) {
        cur_track = left[i];

        // appending current track to seek sequence
        seek_sequence.push_back(cur_track);

        // calculate absolute distance
        distance = abs(cur_track - head);

        // increase the total count
        seek_count += distance;

        // accessed track is now the new head
        head = cur_track;
    }

    cout << "Total number of seek operations = "
         << seek_count << endl;

    cout << "Seek Sequence is" << endl;

    for (int i = 0; i < seek_sequence.size(); i++) {
        cout << seek_sequence[i] << endl;
    }
}
void main2(){int m[10],p[10],i,n,j=0,low=999,li,s=0,nm,c=0;
    cout<<"enter number of memory blocks"<<endl;
    cin>>nm;
    cout<<"enter memory block sizes"<<endl;
    for(i=0; i<nm; i++)
    {
        cin>>m[i];
    }
    cout<<"enter number of processes"<<endl;
    cin>>n;
    cout<<"enter process sizes"<<endl;
    for(i=0; i<n; i++)
    {
        cin>>p[i];
    }
    for(i=0; i<n; i++)
    {
        int startj = j;
        int wc = 0;
        while (j < nm)
        {
            if(startj == j && wc != 0)
            {
                //cout<<"this cannot be allocated"<<endl;
                c = 0;
                break;
            }
            else{
                wc++;
                if(p[i]<m[j] && m[j]!=0)
                {
                    li=j;
                    c=1;
                    break;
                }
                j = (j + 1) % nm;
                //cout<<"i am j and nm"<<j<<": "<<nm<<endl;
            }

        }

        if(c==1)
        {
        cout<<"process of size "<<p[i]<<"kb "<<"allocated to memory block "<<m[li]<<"kb"<<endl;
         s=s+(m[li]-p[i]);
         m[li]=0;
        }
        if(c==0)
            cout<<p[i]<<"kb not allocated"<<endl;
        c=0;
    }
      for(i=0; i<nm; i++)
    {
            s=s+m[i];
    }
    cout<<"unused space= "<<s<<endl;}
void main3(){    cout << "enter the total disk size" << endl;
    int disk;
    cin >> disk;
    cout << "enter the number of requests" << endl;
    int req;
    cin >> req;
    int arr[req];
    cout << "enter the initial head position" << endl;
    int head;
    cin >> head;
    cout << "enter the request sequence" << endl;
    for(int x=0;x<req;x++)
    {
        cin >> arr[x];
    }
    CSCAN(arr, head);}
void main4(){int status = -2;

  cout<<"Enter 0 if you want to add a file."<<endl;
  cout<<"Enter 1 if you want to add a folder."<<endl;
  cout<<"Enter 2 if you want to delete a file."<<endl;
  cout<<"Enter 3 if you want to delete a folder."<<endl;
  cout<<"Enter 4 if you want to add a file in a folder."<<endl;
  cout<<"Enter 5 if you want to add folder in a folder"<<endl;
  cout<<"Enter 6 if you want to delete a file in a folder"<<endl;
  cout<<"Enter 7 if you want to delete a folder in a folder"<<endl;
  cout<<"Enter 8 if you want to know the total number of files and folders"<<endl;
  cout<<endl;
  cin>>status;

  do
  {
    if(status == 0)
    {
        bool cond = add_file();
        if(cond == true)
        {
            cout<<"File added successfully"<<endl;
        }
        else if(cond == false)
        {
            cout<<"File could not be added"<<endl;
        }
    }
    else if(status == 1)
    {
        bool cond = add_folder();
        if(cond == true)
        {
            cout<<"Folder added successfully"<<endl;
        }
        else if(cond == false)
        {
            cout<<"Folder could not be added"<<endl;
        }
    }
    else if(status == 2)
    {
        bool cond = delete_file();
        if(cond == true)
        {
            cout<<"File deleted successfully"<<endl;
        }
        else if(cond == false)
        {
            cout<<"File could not be deleted"<<endl;
        }

    }
    else if(status == 3)
    {
        bool cond = delete_folder();
        if(cond == true)
        {
            cout<<"Folder deleted successfully"<<endl;
        }
        else if(cond == false)
        {
            cout<<"Folder could not be deleted"<<endl;
        }
    }
    else if(status == 4)
    {
       bool cond = add_f_file();
       if(cond == true)
        {
            cout<<"File added successfully"<<endl;
            stat2 = false;
        }
        else if(cond == false)
        {
            cout<<"File could not be added"<<endl;
        }
    }
    else if(status == 5)
    {
        bool cond = add_f_folder();
        if(cond == true)
        {
            cout<<"Folder added successfully"<<endl;
            stat1 = false;
        }
        else if(cond == false)
        {
            cout<<"Folder could not be added"<<endl;
        }
    }
    else if(status == 6)
    {
        bool cond = delete_f_file();
        if(cond == true)
        {
            cout<<"File deleted successfully"<<endl;
            stat3 = false;
        }
        else if(cond == false)
        {
            cout<<"File could not be deleted"<<endl;
        }
    }
    else if(status == 7)
    {
        bool cond = delete_f_folder();
        if(cond == true)
        {
            cout<<"Folder deleted successfully"<<endl;
            stat4 = false;
        }
        else if(cond == false)
        {
            cout<<"Folder could not be deleted"<<endl;
        }
    }
    else if(status == 8)
    {
        cout<<"The total number of files are : "<<no_files<<endl;
        cout<<"The total number of folders are : "<<no_folders<<endl;
    }
    else
    {
        cout<<"Incorrect option "<<endl;
    }

    for(int i=0; i<10; i++)
    {
        cout<<inode_array[i].type<<" ";
    }
    cout<<endl;

    cout<<"Would you like to continue with operations then select of the options "<<endl;
    cin>>status;
  }while((status == 0)||(status == 1)||(status == 2)||(status == 3)||(status == 4)||(status == 5)||(status == 6)||(status == 7)||(status == 8));
  cout<<endl;}

int main()
{
    cout<<"Enter 1 to perform process management- preemptive SJF"<<endl;
    cout<<"Enter 2 to perform memory management- next fit"<<endl;
    cout<<"Enter 3 to perform I/O management- "<<endl;
    cout<<"Enter 4 to perform file management- Ext2 file system"<<endl;
    int sw;
    cin>>sw;
    switch(sw){
        case 1:
            main1();
            break;
        case 2:
            main2();
            break;
        case 3:
            main3();
            break;
        case 4:
            main4();
            break;
        default:
            cout<<"Choose correct option"<<endl;

    }
}

