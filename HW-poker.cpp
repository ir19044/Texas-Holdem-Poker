#include <iostream>
#include <fstream>
#include <string>
using namespace std;

class Poker{
private:
    char h1; ///first card (hand)
    char h2; ///second card (hand)
    char s1; ///first suit (hand)
    char s2; ///second suit (hand)
    string comb; ///Best comb for player
    char note1; ///Note about comb to compare with others
    char note2; ///Note about comb to compare with others
    char note3; ///Note about comb to compare with others
    char note4; ///Note about comb to compare with others
public:
    Poker(const char ha1='2', const char ha2='2', const char su1='c', const char su2='s', const string c="Royal",const char n1='T', const char n2='A',const char n3='K',const char n4='Q'){
        set_hands(ha1,ha2);
        set_suits(su1,su2);
        set_comb(c);
        set_notes(n1,n2,n3,n4);
    }

    void set_hands(const char a,const char b) {h1=a; h2=b;}
    void set_suits(const char a,const char b) {s1=a; s2=b;}
    void set_comb(const string a) {comb=a;}
    void set_notes(const char a,const char b, const char c,const char d) {note1=a; note2=b; note3=c;note4=d;}
    char get_1card() {return h1;}
    char get_2card() {return h2;}
    char get_1suit() {return s1;}
    char get_2suit() {return s2;}
    string get_comb() {return comb;}
    char get_note1() {return note1;}
    char get_note2() {return note2;}
    char get_note3() {return note3;}
    char get_note4() {return note4;}


    void combinations(char mas[][2]){
        char st[5][2];
        sort_me(mas); ///Sort cards to define combinations in the future
        high_card(mas);
        StraightFlush(mas); ///and Royale
        if(get_comb()=="High") FourKind(mas); ///Find combination until get_comb() will be changed
        if(get_comb()=="High") FullHouse(mas);
        if(get_comb()=="High") Flushh(mas);
        if(get_comb()=="High") Straight(mas);
        if(get_comb()=="High") ThreeKind(mas);
        if(get_comb()=="High") Pair_TwoPairs(mas);
    };

    void defgame(string c){ ///One row only for one game
        char mas[7][2]; ///Box/array to define combination for 1 player

        int k=10, l=0, t=0, r=0,tmp=0;
        l = c.length(); ///length of row
        while(t<=l){ ///How many players is?
            if(c[t]==' ' && c[t+1]!=' ') r++; ///r=count of players
            t++;
        }
        char notes[r][4]; ///Array of notes
        string comb[r]; ///Array of combinations
        char hands[r][4];

        t=0;
        while(k<l){
            for(int i=0; i<5; i++) { ///mas - BOX
                for(int j=0; j<2; j++){
                    mas[i][j] = c[tmp];
                    tmp++;
                }
            }
            tmp=0;
            if(c[k]==' ') {k++;continue;}
            else{ ///if find player =>FIND COMBINATION
                set_hands(c[k],c[k+2]);
                set_suits(c[k+1],c[k+3]);
                hands[t][0]=get_1card();
                hands[t][1]=get_1suit();
                hands[t][2]=get_2card();
                hands[t][3]=get_2suit();
                for(int i=5; i<7; i++) {
                    for(int j=0; j<2; j++){
                        mas[i][j]=c[k];
                        k++;
                    }
                }
            }
            combinations(mas);
            notes[t][0]=get_note1();
            notes[t][1]=get_note2();
            notes[t][2]=get_note3();
            notes[t][3]=get_note4();
            comb[t]=get_comb();
            t++;
        }
        sort_players(notes,comb,hands,t);
    };

    int compare_comb(string x, string y){
        int a,b;
        if(x=="High") a=1;
        if(x=="Pair") a=2;
        if(x=="TwoPairs") a=3;
        if(x=="ThreeKind") a=4;
        if(x=="Straight") a=5;
        if(x=="Flush") a=6;
        if(x=="FullHouse") a=7;
        if(x=="FourKind") a=8;
        if(x=="StraightFlush") a=9;
        if(x=="Royale") a=10;

        if(y=="High") b=1;
        if(y=="Pair") b=2;
        if(y=="TwoPairs") b=3;
        if(y=="ThreeKind") b=4;
        if(y=="Straight") b=5;
        if(y=="Flush") b=6;
        if(y=="FullHouse") b=7;
        if(y=="FourKind") b=8;
        if(y=="StraightFlush") b=9;
        if(y=="Royale") b=10;

        if(a>b) return 1;
        else if(a<b) return -1;
            else return 0;
    }

    int compare_similarcombination(char n11, char n12, char n13, char n14,char n21, char n22, char n23, char n24){
        int U=0;
        U=compare_me(n11,n21);
        if(U>0) return 1;
        else if(U<0) return -1;
        else{
            U=compare_me(n12,n22);
            if(U>0) return 1;
            else if(U<0) return -1;
            else{
                U=compare_me(n13,n23);
                if(U>0) return 1;
                else if(U<0) return -1;
                else{
                    U=compare_me(n14,n24);
                    if(U>0) return 1;
                    else if(U<0) return -1;
                    else return 0;
                }
            }
        }
    }

    void sort_players(char notes[][4], string comb[],char hands[][4], int dim){
        bool flag=true;
        char  tmp1;
        int a;
        string tmp;
        dim--;
        while(flag==true){
            flag=false;
            for(int i=0; i<dim; i++){
                if(compare_comb(comb[i],comb[i+1])>0){
                    tmp=comb[i]; ///best comb to the end of row
                    comb[i]=comb[i+1]; ///SORT array of combinations
                    comb[i+1]=tmp;

                    tmp1=hands[i][0];  ///SORT array of hands
                    hands[i][0]=hands[i+1][0];
                    hands[i+1][0]=tmp1;
                    tmp1=hands[i][1];
                    hands[i][1]=hands[i+1][1];
                    hands[i+1][1]=tmp1;
                    tmp1=hands[i][2];
                    hands[i][2]=hands[i+1][2];
                    hands[i+1][2]=tmp1;
                    tmp1=hands[i][3];
                    hands[i][3]=hands[i+1][3];
                    hands[i+1][3]=tmp1;


                    tmp1=notes[i][0];  ///SORT array of notes
                    notes[i][0]=notes[i+1][0];
                    notes[i+1][0]=tmp1;

                    tmp1=notes[i][1];
                    notes[i][1]=notes[i+1][1];
                    notes[i+1][1]=tmp1;

                    tmp1=notes[i][2];
                    notes[i][2]=notes[i+1][2];
                    notes[i+1][2]=tmp1;

                    tmp1=notes[i][3];
                    notes[i][3]=notes[i+1][3];
                    notes[i+1][3]=tmp1;
                    flag=true;
                } else if(compare_comb(comb[i],comb[i+1])==0){

                    a=compare_similarcombination(notes[i][0],notes[i][1],notes[i][2],notes[i][3],notes[i+1][0],notes[i+1][1],notes[i+1][2],notes[i+1][3]);
                    if(comb[i]=="Straight" || comb[i]=="StraightFlush"){
                        if(notes[i][0]=='2' && notes[i+1][0]=='A') a=1;
                        else a=0;
                    }


                    if(a==1){ ///if is similar combinations, but no equal by strenth
                        tmp=comb[i]; ///best comb to the end of row
                        comb[i]=comb[i+1];
                        comb[i+1]=tmp;

                        tmp1=hands[i][0];
                        hands[i][0]=hands[i+1][0];
                        hands[i+1][0]=tmp1;
                        tmp1=hands[i][1];
                        hands[i][1]=hands[i+1][1];
                        hands[i+1][1]=tmp1;
                        tmp1=hands[i][2];
                        hands[i][2]=hands[i+1][2];
                        hands[i+1][2]=tmp1;
                        tmp1=hands[i][3];
                        hands[i][3]=hands[i+1][3];
                        hands[i+1][3]=tmp1;

                        tmp1=notes[i][0];
                        notes[i][0]=notes[i+1][0];
                        notes[i+1][0]=tmp1;

                        tmp1=notes[i][1];
                        notes[i][1]=notes[i+1][1];
                        notes[i+1][1]=tmp1;

                        tmp1=notes[i][2];
                        notes[i][2]=notes[i+1][2];
                        notes[i+1][2]=tmp1;

                        tmp1=notes[i][3];
                        notes[i][3]=notes[i+1][3];
                        notes[i+1][3]=tmp1;
                        flag=true;
                    }

                }
            }
        }
        output_players(hands,notes,comb,dim);
    }

    void sort_me(char mas[][2]){
        bool flag=1;
        char  tmp1,tmp2;
        while(flag==true){
            flag=false;
            for(int i=0; i<6; i++){
                if(compare_me(mas[i][0],mas[i+1][0])>0){
                    tmp1=mas[i][0]; ///big number to the end of row
                    tmp2=mas[i][1];
                    mas[i][0]=mas[i+1][0];
                    mas[i][1]=mas[i+1][1];
                    mas[i+1][0]=tmp1;
                    mas[i+1][1]=tmp2;
                    flag=true;
                }
            }
        }
    };

    int compare_me(char a, char b){
        int x=0,y=0;
        if(a>='2' && a<='9') x=(int)a-48;
        else{
            switch(a) {
              case 'T':
                x=10;
                break;
              case 'J':
                x=11;
                break;
              case 'Q':
                x=12;
                break;
              case 'K':
                x=13;
                break;
              case 'A':
                x=14;
                break;
            }
        }
        if(b>='2' && b<='9') y=int(b)-48;
        else{
            switch(b) {
              case 'T':
                y=10;
                break;
              case 'J':
                y=11;
                break;
              case 'Q':
                y=12;
                break;
              case 'K':
                y=13;
                break;
              case 'A':
                y=14;
                break;
            }
        }
        if(x>y) return 1;
        else if(x<y) return -1;
        else return 0;
    }

    int delta(char a, char b){
        int x=0,y=0;
        if(a>='2' && a<='9') x=(int)a-48;
        else{
            switch(a) {
              case 'T':
                x=10;
                break;
              case 'J':
                x=11;
                break;
              case 'Q':
                x=12;
                break;
              case 'K':
                x=13;
                break;
              case 'A':
                x=14;
                break;
            }
        }
        if(b>='2' && b<='9') y=int(b)-48;
        else{
            switch(b) {
              case 'T':
                y=10;
                break;
              case 'J':
                y=11;
                break;
              case 'Q':
                y=12;
                break;
              case 'K':
                y=13;
                break;
              case 'A':
                y=14;
                break;
            }
        }
        if((x==14 && y==2) || (y==14 && x==2)) return 1;
        else return abs(x-y);
    }

    void high_card(char mas [][2]){
        set_comb("High");
        char fl[5],n1='0',n2='0';
        int j=0;
        for(int i=6; i>=0; i--){
            fl[j]=mas[i][0]; ///fl[] array of top 5 cards
            j++;
            if(j==5) break;
        }
        for(int i=0; i<5; i++){
            if(fl[i]==get_1card() || fl[i]==get_2card() ){ ///if fl[] card equal to hands cards
                if(n1=='0') n1=fl[i];
                else {
                    n2=fl[i];
                    break;
                }
            }
        }
        set_notes(n1,n2,'0','0');
    };

    void Pair_TwoPairs(char mas[][2]){
        int pairs=0;
        int q=0;
        char tmp1='0',tmp2='0',tmp3='0', kicker='0',kicker2='0',kicker3='0';
        for(int i=0; i<7; i++){
            for(int j=i; j<6; j++){
                if(mas[i][0]==mas[j+1][0]){ ///if pair is found
                    pairs++;
                    if(tmp1=='0') tmp1=mas[j+1][0]; ///What pair?
                    else if(tmp2=='0') tmp2=mas[j+1][0];
                    else if(tmp3=='0') tmp3=mas[j+1][0];
                } else break;
            }
        }

        if(pairs>1){
            set_comb("TwoPairs");
            if(tmp3=='0'){
                for(int i=6;i>=0;i--){ ///FIND 5th card, or kicker
                    if(mas[i][0]==tmp1 || mas[i][0]==tmp2) continue;
                    else {kicker=mas[i][0]; break;}
                }
            } else{
                for(int i=6;i>=0;i--){ ///FIND 5th card, or kicker
                    if(mas[i][0]==tmp2 || mas[i][0]==tmp3) continue;
                    else {kicker=mas[i][0]; break;}
                }
            }
            if(tmp3=='0') set_notes(tmp2,tmp1,kicker,'0');
            else set_notes(tmp3,tmp2,kicker,'0');
        }
        if(pairs==1){
            set_comb("Pair");
            for(int i=6;i>=0;i--){ ///FIND 3rd,4th,5th card, or kickers
                if(mas[i][0]==tmp1) continue;
                else {
                    if(kicker=='0') kicker=mas[i][0];
                    else if(kicker2=='0') kicker2=mas[i][0];
                    else if(kicker3=='0') kicker3=mas[i][0];
                }
            }
            set_notes(tmp1,kicker,kicker2,kicker3);
        }
    }

    void FourKind(char mas[][2]){
        int pairs=1;
        char kicker='0';
        for(int i=0; i<7; i++){
            pairs=1;
            for(int j=i; j<6; j++){
                if(mas[i][0]==mas[j+1][0]){ ///if find one pair
                    pairs++;
                }
            }
            if(pairs==4){
                set_comb("FourKind");
                for(int j=0;j<7;j++){ ///FIND 5th card, or kicker
                    if(mas[j][0]==mas[i][0]) continue;
                    else kicker=mas[j][0];
                }
                set_notes(mas[i][0],kicker,'0','0');
            }
        }
    }

    void ThreeKind(char mas[][2]){
        int pairs=1;
        char kicker='0',kicker2='0';
        for(int i=0; i<7; i++){
            pairs=1;
            for(int j=i; j<6; j++){
                if(mas[i][0]==mas[j+1][0]){ ///if find one pair but NOT more than 3
                    pairs++;
                }
            }
            if(pairs==3){
                set_comb("ThreeKind");
                for(int j=6;j>=0;j--){ ///FIND 4th,5th card, or kickers
                    if(mas[j][0]==mas[i][0]) continue;
                    else {
                        if(kicker=='0') kicker=mas[j][0];
                        else if(kicker2=='0') kicker2=mas[j][0];
                    }
                }
                set_notes(mas[i][0],kicker,kicker2,'0');
            }
        }
    }

    void Flushh(char mas[][2]){
        int h=0,d=0,c=0,s=0, j=0;
        char T='0', fl[5], n1='0',n2='0';
        for(int i=0; i<7; i++){
            if(mas[i][1]=='h') h++;
            else if(mas[i][1]=='d') d++;
            else if(mas[i][1]=='c') c++;
            else if(mas[i][1]=='s') s++;
        }
        if(h>=5) T='h';
        else if(d>=5) T='d';
        else if(c>=5) T='c';
        else if(s>=5) T='s';
        else T='0';
        if(T!='0'){ ///if find 5 same suits
            set_comb("Flush");

            for(int i=6; i>=0; i--){
                if(mas[i][1]==T) {
                    fl[j]=mas[i][0];
                    j++;
                }
                if(j==5) break;
            }
            for(int i=0; i<5; i++){
                if((fl[i]==get_1card() && get_1suit()==T) || (fl[i]==get_2card() && get_2suit()==T)){
                    if(n1=='0') n1=fl[i];
                    else {
                        n2=fl[i];
                        break;
                    }
                }
            }
            set_notes(n1,n2,'0','0');
        }
    }

    void Straight(char mas[][2]){
        int card=1, sub=0, tmp=1;
        char T[5][2];
        for(int i=0; i<7; i++){
            tmp=1;
            card=1;
            T[0][0]=mas[i][0];
            T[0][1]=mas[i][1];
            for(int j=i; j<6; j++){
                sub=delta(mas[j+1][0],mas[j][0]); ///if substraction of 2 cards is 1 or 0 => continue =>find straight
                if(sub==1) {
                    card++;
                    T[tmp][0]=mas[j+1][0];
                    T[tmp][1]=mas[j+1][1];
                    tmp++;
                } else if(sub!=0) break;
            }
            if(card>=5){
                set_comb("Straight");
                set_notes(T[0][0],T[4][0],'0','0'); ///MAX&MIN for straight
            }
            if(card==4 && mas[i][0]=='2' && mas[6][0]=='A'){
                set_comb("Straight");
                set_notes('A','5','0','0'); ///MAX&MIN for straight
            }
        }
    };

    void StraightFlush(char mas[][2]){
        char S; ///Sign for StraightFlush
        int h=0,d=0,c=0,s=0;
        bool flag1=false,flag=true;
        for(int i=0; i<7; i++){
            if(mas[i][1]=='h') h++;
            else if(mas[i][1]=='d') d++;
            else if(mas[i][1]=='c') c++;
            else s++;
        }
        if(h>=5) {S='h';flag1=true;}
        if(d>=5) {S='d';flag1=true;}
        if(c>=5) {S='c';flag1=true;}
        if(s>=5) {S='s';flag1=true;}

        int card=1, sub=0, tmp=1;
        char T[5][2];
        if(flag1){
            for(int i=0; i<7; i++){
                flag=true;
                tmp=1;
                card=1;
                T[0][0]=mas[i][0];
                T[0][1]=mas[i][1];
                for(int j=i; j<6; j++){
                    sub=delta(mas[j+1][0],mas[j][0]);
                    if(sub==1 || sub==0){ ///if delta of 2 cards==1 or cards repeats
                        if(sub==1) {
                            card++;
                            T[tmp][0]=mas[j+1][0];
                            T[tmp][1]=mas[j+1][1];
                            tmp++;
                        } else if(sub==0 && mas[j+1][1]==S){
                            T[tmp-1][0]=mas[j+1][0]; ///for royal OR StraightFlush
                            T[tmp-1][1]=mas[j+1][1];
                        }
                    } else break;
                }
                if(card>=5){
                    for(int i=0;i<4;i++){
                        if(T[i][1]==T[i+1][1]) continue;
                        else {flag=false; break;}
                    }
                    if(flag){ ///Is straight and flush for one and the same cards?
                        if(T[0][0]=='T'){
                            set_comb("Royale");
                            set_notes('0','0','0','0');
                        }else{
                            set_comb("StraightFlush");
                            set_notes(T[0][0],T[4][0],'0','0'); ///MAX&MIN for straight
                        }
                    }
                }
                if(card==4 && T[0][0]=='2'){
                    for(int i=0;i<3;i++){
                        if(T[i][1]==T[i+1][1]) continue;
                        else {flag=false; break;}
                    }
                    if(flag){ ///Is straight and flush for one and the same cards?
                        for(int i=6; i>3; i--){
                            if(mas[i][0]=='A' && mas[i][1]==T[0][1]){
                                set_comb("StraightFlush");
                                set_notes('A','5','0','0'); ///MAX&MIN for straight
                                break;
                            }
                        }
                    }
                }
            }
        }
    };

    void FullHouse(char mas[][2]){
        int t=1;
        char S='0',P='0';
        for(int i=0; i<7; i++){
            for(int j=i; j<6; j++){
                if(mas[i][0]==mas[j+1][0]) t++;
                else break;
            }
            if(t==3) S=mas[i][0];
            if(t==2 && compare_me(mas[i][0],P)>0 && P=='0' && mas[i][0]!=S) P=mas[i][0];
            t=1;
        }
        if(S!='0' && P!='0'){
            set_comb("FullHouse");
            set_notes(S,P,'0','0');
        }
    }

    void output_players(char hands[][4], char notes[][4],string comb[], int dim){
        dim++;
        for(int i=0; i<dim; i++){
            for(int j=0; j<4; j++) cout<<hands[i][j];
            if(i!=dim-1){
                if(compare_comb(comb[i],comb[i+1])==0){
                    if(compare_similarcombination(notes[i][0],notes[i][1],notes[i][2],notes[i][3],notes[i+1][0],notes[i+1][1],notes[i+1][2],notes[i+1][3])==0){
                        cout<<"=";
                    }else cout<<' ';
                }else cout<<' ';
            }else cout<<' ';
        }
    }
};
int main(){


    Poker p;
    string c;
    while(getline(cin,c,'\n')){
        p.defgame(c);
        cout<<"\n";
    }


    system("pause");
    return 0;
}
