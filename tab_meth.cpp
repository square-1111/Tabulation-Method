#include <bits/stdc++.h>
using namespace std;
vector<string>input;
int maxi,store[100000];
//convert decimal to binary
string dec_bin(int num,int var){
	string a;
	int al=0;
	for(;num>0;num/=2){
		char temp=num%2+'0';
		a.push_back(temp);
		al++;
	}
	for(int j=0; j<var-al; j++){
		a.push_back('0');
	}
	reverse(a.begin(),a.end());
	return a;
}
//input vector number of bits= number of variables
void in(int n,int var){
	int num;
	for(int i=0;i<n;i++){
		cin>>num;
		store[i]=num;
		input.push_back(dec_bin(num,var));
	}
}
//check if binary number differ by only one bit
int one_bit(string a,string b){
	int flag=0;
	for(int i=0;i<a.length();i++){
		if(a[i]!=b[i]){flag++;}
	}
	if(flag==1){return 1;}
	return 0;
}
//if bit differ by only one bit we assign that bit -
string elim_if_comp(string a,string b){
	string temp;
	for(int i=0;i<a.size();i++){
		if(a[i]!=b[i]){temp=temp+"-";}
		else{temp=temp+a[i];}
	}
	return temp;
}
//check if temp pre-exist in vector 
int compar(vector<string> a,string b){
	for(int i=0;i<a.size();i++){
		if(a[i].compare(b)==0){return 0;}
	}
	return 1;
}
//comparing two numbers with same bit_one and changing there terms 
vector<string> step2(vector<string>a){
	vector<string>retu_vec;
	retu_vec.clear();
	int *flag;
	flag=new int[a.size()];
	memset(flag,0,sizeof (flag));
	for(int i=0;i<a.size();i++){
		for(int j=i;j<a.size();j++){
			if(one_bit(a[i],a[j])){
				flag[i]=flag[j]=1;
				if(compar(retu_vec,elim_if_comp(a[i],a[j]))){
					retu_vec.push_back(elim_if_comp(a[i],a[j]));
				}
			}
		}
	}
	for(int i=0;i<a.size();i++){
        if(flag[i]!=1 && compar(retu_vec,a[i])){
           retu_vec.push_back(a[i]);
        }
      }
    //free(flag);
	return retu_vec;
}
int compare_vect(vector<string>a,vector<string>b){
	sort(a.begin(),a.end());
	sort(b.begin(),b.end());
	for(int i=0;i<a.size();i++){
		if(a[i]!=b[i]){return 1;}
	}
	return 0;
}
int coun(string a){
	int cou=0;
	for(int i=0;a[i];i++){
		cou+=a[i]=='-'?1:0;
	}
	return cou;
}
vector<string> sortin(vector<string>in){
	vector<pair<int,string> >gullu;
	for(int i=0;i<input.size();i++){
		gullu.push_back(make_pair(coun(input[i]),input[i]));
	}
	sort(gullu.begin(),gullu.end());
	vector<string>hofaba;
	for(int i=0;i<gullu.size();i++){
		hofaba.push_back(gullu[i].second);
	}
	return hofaba;
}

int dash_compare(string a,string b){
	for(int i=0;i<a.length();i++){
		if(a[i]!=b[i]&&a[i]!='-'){return 0;}
	}
	return 1;
}


int main(){
	//input
	int n,var;
	cout<<"number of variables are ";
	cin>>var;
	if(var==0){return puts("This ain't possible");}
	cout<<"number of elements you want to input (cannot be more than "<<pow(2,var)<<") ";
	cin>>n;
	string all_dash(var,'-');
	if(n>0){cout<<"min terms between 0 to "<<pow(2,var)-1<<" "<<endl;}
	in(n,var);
	cout<<"Do you want dont care condition(y/n)";
	char ch;
	cin>>ch;
	if(ch==tolower('Y')){
		int k;
		cout<<"Number of Dont care terms are ";
		cin>>k;
		int *dont=new int[k];
		cout<<"Give dont care terms";
		for(int i=0;i<k;i++){
			cin>>dont[i];
			input.push_back(dec_bin(dont[i],var));
		}
	}
	if(n==0){return puts("Function cant be Minimized");}
	//determination of prime implicant
	sort(store,store+n);
	while(compare_vect(input,step2(input))){
		input=step2(input);
	}
	input=sortin(input);
	int **gra=new int*[input.size()];
	for(int i=0;i<input.size();i++){
		gra[i]=new int[n];
	}
	for(int i=0;i<input.size();i++){
		for(int j=0;j<n;j++){
			gra[i][j]=0;
			if(dash_compare(input[i],dec_bin(store[j],var))){gra[i][j]=1;}
		}
	}
	//selection of prime implicant
	vector<string>output;
	output.clear();
	int check_val=1;
	while(1){
		if(check_val==0){break;}
		check_val=0;
		for(int i=0;i<n;i++){
			for(int j=0;j<input.size();j++){
				if(gra[j][i]!=0){check_val=1;break;}
			}
			if(check_val==1){break;}
		}
		
		vector<int>count_1;
		//count number of ones and push it to count_1
		for(int i=0;i<n;i++){
			int abc=0;
			for(int j=0;j<input.size();j++){
				if(gra[j][i]==1){abc++;}
			}
			count_1.push_back(abc);
		}
		vector<int>mini_inde;
		int mini=input.size()+1;
		//compute minimum number of 1's 
		for(int i=0;i<count_1.size();i++){
			if(mini>count_1[i]&&count_1[i]>0){mini=count_1[i];}
		}
		//find columns where number of ones are min
		for(int i=0;i<count_1.size();i++){
			if(count_1[i]==mini){mini_inde.push_back(i);}
		}
		//from column note the index of row where there is 1
		vector<int>notej;
		for(int i=0;i<mini_inde.size();i++){
			for(int j=0;j<input.size();j++){
				if(gra[j][mini_inde[i]]==1){notej.push_back(j);}
			}
		}

		//remove repeated elements
		sort(notej.begin(),notej.end());
		vector<int>::iterator it;
		it = unique (notej.begin(), notej.end());
		notej.resize( std::distance(notej.begin(),it));
		//note number of ones in selected rows
		vector<pair<int,int> >row_1;
		for(int i=0;i<notej.size();i++){
			int rubber=0;
			for(int j=0;j<n;j++){
				if(gra[notej[i]][j]==1){rubber++;}
			}
			row_1.push_back(make_pair(rubber,notej[i]));
		}
		//find max of number of the 1s in row
		int max=0,notein;
		for(int i=0;i<row_1.size();i++){
			if(max<row_1[i].first){max=row_1[i].first;notein=row_1[i].second;}
		}
		//cout<<notein<<"  hello we are at 1"<<endl;
		output.push_back(input[notein]);
		for(int i=0;i<n;i++){
			if(gra[notein][i]==1){
				for(int j=0;j<input.size();j++){
					gra[j][i]=0;
				}
			}
		}
		count_1.clear();
		mini_inde.clear();
		notej.clear();
		row_1.clear();
	}
	sort(output.begin(),output.end());
	auto it = unique (output.begin(), output.end());
	output.resize( std::distance(output.begin(),it));
	//output=sortin(output);
	cout<<"Minimized function is: ";
	for(int i=0;i<output.size()-1;i++){
		cout<<"<"<<output[i]<<"> + ";
	}
	cout<<"<"<<output[output.size()-1]<<">"<<endl;
}

