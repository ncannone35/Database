#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct CSG* CSGlist;
struct CSG{//course-ID-grade
	char *course;
	char *studentId;
	char *grade;
    	CSGlist next;
	CSGlist prev;
};

typedef struct SNAP* SNAPlist;
struct SNAP{//ID-name-address-phone number
	char *studentId;
	char *name;
	char *address;
	char *phone;
	SNAPlist next;
	SNAPlist prev;
};

typedef struct CP* CPlist;
struct CP{//course-prereq
	char *course;
	char *pre;
	CPlist next;
	CPlist prev;
};

typedef struct CDH* CDHlist;
struct CDH{//course-day-hour
	char *course;
	char *day;
	char *hour;
	CDHlist next;
	CDHlist prev;
};

typedef struct CR* CRlist;
struct CR{//course-room
	char *course;
	char *room;
	CRlist next;
	CRlist prev;
};

CSGlist newCSG(char* c, char* s, char* g){
	CSGlist curr = (CSGlist)malloc(sizeof(struct CSG));
	curr->course = c;
	curr->studentId = s;
	curr->grade = g;
	curr->next = NULL;
	curr->prev = NULL;
	return curr;
}

SNAPlist newSNAP(char *s, char* n, char* a, char* p){
	SNAPlist curr = (SNAPlist)malloc(sizeof(struct SNAP));
	curr->studentId = s;
	curr->name = n;
	curr->address = a;
	curr->phone = p;
	curr->next = NULL;
	curr->prev = NULL;
	return curr;
}

CPlist newCP(char* c, char* p){
	CPlist curr = (CPlist)malloc(sizeof(struct CP));
	curr->course = c;
	curr->pre = p;
	curr->next = NULL;
	curr->prev = NULL;
	return curr;
}

CDHlist newCDH(char* c, char* d, char* h){
	CDHlist curr = (CDHlist)malloc(sizeof(struct CDH));
	curr->course = c;
	curr->day = d;
	curr->hour = h;
	curr->next = NULL;
	curr->prev = NULL;
	return curr;
}

CRlist newCR(char* c, char* r){
	CRlist curr = (CRlist)malloc(sizeof(struct CR));
	curr->course = c;
	curr->room = r;
	curr->next = NULL;
	curr->prev = NULL;
	return curr;
}

void print_CSG(CSGlist csg){
  while(csg!=NULL){
    printf("         %s          %s           %s\n", csg->course, csg->studentId, csg->grade);
    csg = csg->next;
  }
}

void print_SNAP(SNAPlist csg){
  while(csg!=NULL){
    printf("         %s          %s            %s           %s\n", csg->studentId, csg->name, csg->address, csg->phone);
    csg = csg->next;
  }
}

void print_CP(CPlist csg){
  while(csg!=NULL){
    printf("           %s           %s\n", csg->course, csg->pre);
    csg = csg->next;
  }
}

void print_CDH(CDHlist csg){
  while(csg!=NULL){
    printf("            %s             %s            %s\n", csg->course, csg->day, csg->hour);
    csg = csg->next;
  }
}

void print_CR(CRlist csg){
  while(csg!=NULL){
    printf("            %s         %s\n", csg->course, csg->room);
    csg = csg->next;
  }
}

int compCSG(CSGlist l1, CSGlist l2){
	if(strcmp(l1->course, l2->course)==0 && strcmp(l1->studentId, l2->studentId)==0 && strcmp(l1->grade, l2->grade)==0) return 1;
	else return 0;
}

int compSNAP(SNAPlist l1, SNAPlist l2){
  if(strcmp(l1->studentId, l2->studentId) && strcmp(l1->name, l2->name)==0 && strcmp(l1->address, l2->address)==0 && strcmp(l1->phone, l2->phone)==0) return 1;
  else return 0;
}

int compCDH(CDHlist l1, CDHlist l2){
	if(strcmp(l1->course, l2->course)==0 && strcmp(l1->day, l2->day)==0 && strcmp(l1->hour, l2->hour)==0) return 1;
	else return 0;
}

int compCP(CPlist l1, CPlist l2){
	if(strcmp(l1->course, l2->course)==0 && strcmp(l1->pre, l2->pre)==0) return 1;
	else return 0;
}

int compCR(CRlist l1, CRlist l2){
	if(strcmp(l1->course, l2->course)==0 && strcmp(l1->room, l2->room)==0)return 1;
	else return 0;
}
//hashtables

CSGlist csg_table[97];
SNAPlist snap_table[97];
CPlist cp_table[97];
CDHlist cdh_table[97];
CRlist cr_table[97];


//hash functions

int sumChar(char* str){
	int sum = 0;
	for(int i =0; i < strlen(str); i++)
		sum+=str[i];
	return sum;
}
	
int hash_function(char* str){
	return sumChar(str) % 97;
}



//insertions

void insertCSG(CSGlist csg){
	char fill[10];
	strcpy(fill, csg->course);
	strcat(fill, csg->grade);
	int hash = hash_function(fill);
	if(csg_table[hash] != NULL){
		CSGlist curr = csg_table[hash];
		int copy = 0;
		if(compCSG(csg, curr))
			copy++;
		while(curr->next != NULL && copy==0){
			if(compCSG(csg, curr))
				copy ++;;
			curr=curr->next;
		}
		if(copy >> 0){
			printf("Error: the CSG relation already exists:");
			print_CSG(csg);
		}
		else
			curr->next=csg;
	}else{ 
		csg_table[hash] = csg;
	}
}

void insertSNAP(SNAPlist snap){
	int hash = hash_function(snap->studentId);
	if(csg_table[hash] != NULL){
		SNAPlist curr = snap_table[hash];
		int copy = 0;
		if(compSNAP(snap, curr))
			copy++;
		while(curr->next != NULL && copy==0){
			if(compSNAP(snap, curr))
				copy = 1;
			curr=curr->next;
		}
		if(copy >> 0){
			printf("Error: the SNAP relation already exists:");
			print_SNAP(snap);
		}
		else
			curr->next=snap;
	}else{ 
		snap_table[hash] = snap;
	}
}

void insertCP(CPlist cp){
	char course[10];
	strcpy(course, cp->course);
	strcat(course, cp->pre);
	int hash = hash_function(course);
	if(cp_table[hash] != NULL){
		CPlist curr = cp_table[hash];
		int copy = 0;
		if(compCP(cp, curr))
			copy++;
		while(curr->next != NULL){
			if(compCP(cp, curr)){
				copy ++;
				break;
			}
			curr=curr->next;
		}
		if(copy >> 0){
			printf("Error: the CP relation already exists:");
			print_CP(cp);
		}
		else
			curr->next=cp;
	}else{ 
		cp_table[hash] = cp;
	}
}

void insertCDH(CDHlist cdh){
	char course_day[7];
	strcpy(course_day, cdh->course);
	strcat(course_day, cdh->day);
	int hash = hash_function(course_day);
	if(cdh_table[hash] != NULL){
		CDHlist curr = cdh_table[hash];
		int copy = 0;
		if(compCDH(cdh, curr))
			copy++;
		while(curr->next != NULL && copy==0){
			if(compCDH(cdh, curr))
				copy = 1;
			curr=curr->next;
		}
		if(copy >> 0){
			printf("Error: the CDH relation already exists:");
			print_CDH(cdh);
		}
		else
			curr->next=cdh;
	}else{ 
		cdh_table[hash] = cdh;
	}
}

void insertCR(CRlist cr){
	int hash = hash_function(cr->room);
	if(cr_table[hash] != NULL){
		CRlist curr = cr_table[hash];
		int copy = 0;
		if(compCR(cr, curr))
			copy++;
		while(curr->next != NULL && copy==0){
			if(compCR(cr, curr))
				copy = 1;
			curr=curr->next;
		}
		if(copy >> 0){
			printf("Error: the CR relation already exists:");
			print_CR(cr);
		}
		else
			curr->next=cr;
	}else{ 
		cr_table[hash] = cr;
	}
}

void deleteCSG(char* c, char* s, char* g){
	for(int i = 0; i < 97; i ++){
		if(csg_table[i] != NULL){
			CSGlist curr = csg_table[i];
			int depth = 0;
			while(curr!=NULL){
				if((strcmp(curr->course, c)==0 || c[0]=='*') && (strcmp(curr->studentId, s)==0 || s[0]=='*') && (strcmp(curr->grade, g)==0 || g[0]=='*')){
					if(depth == 0){
						csg_table[i] = NULL;
						curr=curr->next;
						depth++;
					}else if(curr->next==NULL){
						curr->prev->next = NULL;
						curr=curr->next;
						depth++;
					}else{
						curr->next->prev = curr->prev;
						curr->prev->next = curr->next;
						curr = curr->next;
						depth++;
					}
				}else{
					curr = curr->next;
					depth++;
				}
			}
		}
	}
}

void deleteSNAP(char* s, char* n, char* a, char* p){
	for(int i = 0; i < 97; i ++){
		if(snap_table[i] != NULL){
			SNAPlist curr = snap_table[i];
			int depth = 0;
			while(curr!=NULL){
				if((strcmp(curr->studentId, s)==0 || s[0]=='*') && (strcmp(curr->name, n)==0 || n[0]=='*') && (strcmp(curr->address, a)==0 || a[0]=='*') && (strcmp(curr->phone, p)==0 || p[0]=='*')){
					if(depth == 0){
						snap_table[i] = NULL;
						curr=curr->next;
						depth++;
					}else if(curr->next==NULL){
						curr->prev->next = NULL;
						curr=curr->next;
						depth++;
					}else{
						curr->next->prev = curr->prev;
						curr->prev->next = curr->next;
						curr = curr->next;
						depth++;
					}
				}else{
					curr = curr->next;
					depth++;
				}
			}
		}
	}
}

void deleteCP(char* c, char* p){
	for(int i = 0; i < 97; i ++){
		if(cp_table[i] != NULL){
			CPlist curr = cp_table[i];
			int depth = 0;
			while(curr!=NULL){
				if((strcmp(curr->course, c)==0 || c[0]=='*') && (strcmp(curr->pre, p)==0 || p[0]=='*')){
					if(depth == 0){
						cp_table[i] = NULL;
						curr=curr->next;
						depth++;
					}else if(curr->next==NULL){
						curr->prev->next = NULL;
						curr=curr->next;
						depth++;
					}else{
						curr->next->prev = curr->prev;
						curr->prev->next = curr->next;
						curr = curr->next;
						depth++;
					}
				}else{
					curr = curr->next;
					depth++;
				}
			}
		}
	}
}

void deleteCDH(char* c, char* d, char* h){
	for(int i = 0; i < 97; i ++){
		if(cdh_table[i] != NULL){
			CDHlist curr = cdh_table[i];
			int depth = 0;
			while(curr!=NULL){
				if((strcmp(curr->course, c)==0 || c[0]=='*') && (strcmp(curr->day, d)==0 || d[0]=='*') && (strcmp(curr->hour, h)==0 || h[0]=='*')){
					if(depth == 0){
						cdh_table[i] = NULL;
						curr=curr->next;
						depth++;
					}else if(curr->next==NULL){
						curr->prev->next = NULL;
						curr=curr->next;
						depth++;
					}else{
						curr->next->prev = curr->prev;
						curr->prev->next = curr->next;
						curr = curr->next;
						depth++;
					}
				}else{
					curr = curr->next;
					depth++;
				}
			}
		}
	}
}

void deleteCR(char* c, char* r){
	for(int i = 0; i < 97; i ++){
		if(cr_table[i] != NULL){
			CRlist curr = cr_table[i];
			int depth = 0;
			while(curr!=NULL){
				if((strcmp(curr->course, c)==0 || c[0]=='*') && (strcmp(curr->room, r)==0 || r[0]=='*')){
					if(depth == 0){
						cr_table[i] = NULL;
						curr=curr->next;
						depth++;
					}else if(curr->next==NULL){
						curr->prev->next = NULL;
						curr=curr->next;
						depth++;
					}else{
						curr->next->prev = curr->prev;
						curr->prev->next = curr->next;
						curr = curr->next;
						depth++;
					}
				}else{
					curr = curr->next;
					depth++;
				}
			}
		}
	}
}

void lookupCSG(char* c, char* s, char* g, CSGlist* csg){
	for(int i = 0; i < sizeof(csg); i ++){
		csg[i] = NULL;
	}
	int found = 0;
	for(int i = 0; i < 97; i ++){
		CSGlist curr = csg_table[i];
		while(curr!=NULL){
			if((strcmp(curr->course, c)==0 || c[0]=='*') && (strcmp(curr->studentId, s)==0 || s[0]=='*') && (strcmp(curr->grade, g)==0 || g[0]=='*')){
				csg[found] = curr;
				found++;
			}curr=curr->next;
		}
	}
	if(found == 0){
		printf("Error: The following tuple does not exist in the system:\n");
		print_CSG(newCSG(c,s,g));
	}
}

void lookupSNAP(char* s, char* n, char* a, char* p, SNAPlist* snap){
	for(int i = 0; i < sizeof(snap); i ++){
		snap[i] = NULL;
	}
	int found = 0;
	for(int i = 0; i < 97; i ++){
		SNAPlist curr = snap_table[i];
		while(curr!=NULL){
			if((strcmp(curr->studentId, s)==0 || s[0]=='*') && (strcmp(curr->name, n)==0 || n[0]=='*') && (strcmp(curr->address, a)==0 || a[0]=='*') && (strcmp(curr->phone, p)==0 || p[0]=='*')){
				snap[found] = curr;
				found++;
			}curr=curr->next;
		}
	}
	if(found == 0){
		printf("Error: The following tuple does not exist in the system:\n");
		print_SNAP(newSNAP(s,n,a,p));
	}
}

void lookupCP(char* c, char* p, CPlist* cp){
	for(int i = 0; i < sizeof(cp); i ++){
		cp[i] = NULL;
	}
	int found = 0;
	for(int i = 0; i < 97; i ++){
		CPlist curr = cp_table[i];
		while(curr!=NULL){
			if((strcmp(curr->course, c)==0 || c[0]=='*') && (strcmp(curr->pre, p)==0 || p[0]=='*')){
				cp[found] = curr;
				found++;
			}curr=curr->next;
		}
	}
	if(found == 0){
		printf("Error: The following tuple does not exist in the system:\n");
		print_CP(newCP(c,p));
	}
}

void lookupCDH(char* c, char* d, char* h, CDHlist* cdh){
	for(int i = 0; i < sizeof(cdh); i ++){
		cdh[i] = NULL;
	}
	int found = 0;
	for(int i = 0; i < 97; i ++){
		CDHlist curr = cdh_table[i];
		while(curr!=NULL){
			if((strcmp(curr->course, c)==0 || c[0]=='*') && (strcmp(curr->day, d)==0 || d[0]=='*') && (strcmp(curr->hour, h)==0 || h[0]=='*')){
				cdh[found] = curr;
				found++;
			}curr=curr->next;
		}
	}
}

void lookupCR(char* c, char* r, CRlist* cr){
	for(int i = 0; i < sizeof(cr); i ++){
		cr[i] = NULL;
	}
	int found = 0;
	for(int i = 0; i < 97; i ++){
		CRlist curr = cr_table[i];
		while(curr!=NULL){
			if((strcmp(curr->course, c)==0 || c[0]=='*') && (strcmp(curr->room, r)==0 || r[0]=='*')){
				cr[found] = curr;
				found++;
			}curr=curr->next;
		}
	}
	if(found == 0){
		printf("Error: The following tuple does not exist in the system:\n");
		print_CR(newCR(c,r));
	}
}

void findGrade(char* n, char*c){
	SNAPlist arr1[97];
	CSGlist arr2[97];
	lookupSNAP("*", n, "*", "*", arr1);
	char* s = arr1[0]->studentId;
	lookupCSG(c,s,"*", arr2);
	printf("%s received a letter grade of '%s' in %s.\n ", n, arr2[0]->grade, c);
}

void findStudent(char* n, char* d, char* h){
	CDHlist arr1[5];//list of courses on d at h
	lookupCDH("*", d, h, arr1);
	SNAPlist arr2[97];
	lookupSNAP("*", n, "*", "*", arr2);
	char* id = arr2[0]->studentId;//n's id
	CSGlist arr3[97];
	for(int i = 0; i < 97; i++){
		if(arr1[i]==NULL)
			break;
		lookupCSG(arr1[i]->course, id, "*", arr3);
	}
	CRlist arr4[97];
	lookupCR(arr3[0]->course, "*", arr4);
	printf("%s is in %s at %s on %s.\n", n, arr4[0]->room, h, d);
}	

void selection_CSG(char schema, char* sel, CSGlist* mod){
	for(int i = 0; i < sizeof(mod); i ++)
		mod[i] = NULL;
	if(schema == 'C' || schema == 'c'){
		lookupCSG(sel, "*", "*", mod);
	}
	else if(schema == 'S' || schema == 's'){
		lookupCSG("*", sel, "*", mod);
	}
	else if(schema == 'G' || schema == 'g'){
		lookupCSG("*", "*", sel, mod);
	}
}

typedef struct C* Clist;
struct C{
	char *course;
	Clist next;
	Clist prev;
};

typedef struct S* Slist;
struct S{
	char *studentId;
	Slist next;
	Slist prev;
};

typedef struct G* Glist;
struct G{
	char *grade;
	Glist next;
	Glist prev;
};

Clist newC(char* c){
	Clist curr = (Clist)malloc(sizeof(struct C));
	curr->course = c;
	curr->next = NULL;
	curr->prev = NULL;
	return curr;
}

Slist newS(char* s){
	Slist curr = (Slist)malloc(sizeof(struct S));
	curr->studentId = s;
	curr->next = NULL;
	curr->prev = NULL;
	return curr;
}

Glist newG(char* g){
	Glist curr = (Glist)malloc(sizeof(struct G));
	curr->grade = g;
	curr->next = NULL;
	curr->prev = NULL;
	return curr;
}

void print_C(Clist c){
	while(c!=NULL){
		printf("%s\n", c->course);
		c=c->next;
	}
}

void print_S(Slist s){
	while(s!=NULL){
		printf("%s\n", s->studentId);
		s=s->next;
	}
}

void print_G(Glist g){
	while(g!=NULL){
		printf("%s\n", g->grade);
		g=g->next;
	}
}

void projection_CSG(char schema, CSGlist* csg, Clist* arr1, Slist* arr2, Glist* arr3){
	if(schema == 'C' || schema == 'c'){
		for(int i = 0; i < 97; i ++)
			arr1[i] = NULL;
		for(int i = 0; i < sizeof(csg); i++){
			if(csg[i] == NULL)
				break;
			arr1[i] = newC(csg[i]->course);
		}
	}
	else if(schema == 'S' || schema == 's'){
		for(int i = 0; i < 97; i ++)
			arr2[i] = NULL;
		for(int i = 0; i < sizeof(csg); i++){
			if(csg[i] == NULL)
				break;
			arr2[i] = newS(csg[i]->studentId);
		}
	}
	else if(schema == 'G' || schema == 'g'){
		for(int i = 0; i < 97; i ++)
			arr3[i] = NULL;
		for(int i = 0; i < sizeof(csg); i++){
			if(csg[i] == NULL)
				break;
			arr3[i] = newG(csg[i]->grade);
		}
	}
}

typedef struct CRDH* CRDHlist;
struct CRDH{//course-day-hour
	char *course;
	char *room;
	char *day;
	char *hour;
	CRDHlist next;
	CRDHlist prev;
};

CRDHlist newCRDH(char* c, char* r, char* d, char* h){
	CRDHlist curr = (CRDHlist)malloc(sizeof(struct CRDH));
	curr->course = c;
	curr->room = r;
	curr->day = d;
	curr->hour = h;
	curr->next = NULL;
	curr->prev = NULL;
	return curr;
}

void print_CRDH(CRDHlist csg){
  while(csg!=NULL){
    printf("%s %s %s %s\n", csg->course, csg->room, csg->day, csg->hour);
    csg = csg->next;
  }
}

void join_CDH_CR(CRDHlist* crdh){
	int index = 0;
	CRlist arr2[10];
	for(int i = 0; i < 10; i ++)
		arr2[i] = NULL;
	lookupCR("*", "*", arr2);
	for(int i = 0; i < sizeof(arr2); i ++){
		if(arr2[i]==NULL)
			break;
		CDHlist arr1[10];
		for(int i = 0; i < 10; i ++)
			arr1[i] = NULL;
		lookupCDH(arr2[i]->course, "*", "*", arr1);
		if(arr1[0] != NULL){
			for(int j = 0; j < sizeof(arr1); j ++){
				if(arr1[j] == NULL)
					break;
				crdh[index] = newCRDH(arr2[i]->course, arr2[i]->room, arr1[j]->day, arr1[j]->hour);
				index++;
			}
		}
		
	}
	
}

void selection_CRDH(char schema, char* sel, CRDHlist* table, CRDHlist* mod){
	int index=0;
	if(schema == 'C' || schema == 'c'){
		for(int i = 0; i < sizeof(table); i ++){
			if(table[i]==NULL)
				break;
			if(strcmp(table[i]->course,sel)==0){
				mod[index] = table[i];
				index++;
			}
		}
	}
	else if(schema == 'R' || schema == 'r'){
		for(int i = 0; i < sizeof(table); i ++){
			if(table[i]==NULL)
				break;
			if(strcmp(table[i]->room,sel)==0){
				mod[index] = table[i];
				index++;
			}
		}
	}
	else if(schema == 'D' || schema == 'd'){
		for(int i = 0; i < sizeof(table); i ++){
			if(table[i]==NULL)
				break;
			if(strcmp(table[i]->day,sel)==0){
				mod[index] = table[i];
				index++;
			}
		}
	}
	else if(schema == 'H' || schema == 'h'){
		for(int i = 0; i < sizeof(table); i ++){
			if(table[i]==NULL)
				break;
			if(strcmp(table[i]->hour,sel)==0){
				mod[index] = table[i];
				index++;
			}
		}
	}

}

typedef struct DH* DHlist;
struct DH{
	char *day;
	char *hour;
	DHlist next;
	DHlist prev;
};

DHlist newDH(char* d, char* h){
	DHlist curr = (DHlist)malloc(sizeof(struct DH));
	curr->day = d;
	curr->hour = h;
	curr->next = NULL;
	curr->prev = NULL;
	return curr;
}

void print_DH(DHlist c){
	while(c!=NULL){
		printf("%s %s\n", c->day, c->hour);
		c=c->next;
	}
}

void projection_DH(CRDHlist* crdh, DHlist* proj){
	int index=0;
	for(int i = 0; i < sizeof(crdh); i ++){
		if(crdh[i]==NULL)
			break;
		proj[index] = newDH(crdh[i]->day, crdh[i]->hour);
		index++;
	}
}

void printCSGtable(){
	    printf("CSG table:\n");
	    printf("index     Course      Student ID      Grade\n");
	    for(int i = 0; i < 97; i ++){
		    printf(" %d",i);
		    if(csg_table[i]!=NULL)
		    	print_CSG(csg_table[i]);
		    else
			    printf("  NULL\n");
	    }
}

void printSNAPtable(){
	    printf("SNAP table:\n");
	    printf("                          Student ID          Name           Address          Phone  #\n");
	    for(int i = 0; i < 97; i++){
		    printf("index:   %d      ",i);
		    if(snap_table[i]!=NULL)
			    print_SNAP(snap_table[i]);
		    else
			    printf("NULL\n");
	    }
}
void printCRtable(){
	    printf("Course-Room table:\n");
	    printf("                          Course          Room\n");
	    for(int i = 0; i < 97; i++){
		    printf("index:   %d      ",i);
		    if(cr_table[i]!=NULL)
			    print_CR(cr_table[i]);
		    else
			    printf("NULL\n");
	    }
}
void printCPtable(){
	    printf("Course-Prerequisite table:\n");
	    printf("                          Course          Prerequisite\n");
	    for(int i = 0; i < 97; i++){
		    printf("index:   %d      ",i);
		    if(cp_table[i]!=NULL)
			    print_CP(cp_table[i]);
		    else
			    printf("NULL\n");
	    }
}
int main(){
	//PART 1
	    printf("Preparing tables...\n");
	    insertCSG(newCSG("CS101", "12345", "A"));
	    insertCSG(newCSG("CS101", "67890", "B"));
	    insertCSG(newCSG("EE200", "12345", "C"));
	    insertCSG(newCSG("EE200", "22222", "B+"));
	    insertCSG(newCSG("CS101", "33333", "A-"));
	    insertCSG(newCSG("PH100", "12345", "C+"));



	    insertSNAP(newSNAP("12345", "C. Brown", "12 Apple St.", "555-1234"));
	    insertSNAP(newSNAP("67890", "L. Van Pelt", "34 Pear Ave.", "555-5678"));
	    insertSNAP(newSNAP("22222", "P. Patty", "56 Grape Blvd.", "55-9999"));




	    insertCP(newCP("CS101", "CS100"));
	    insertCP(newCP("EE200", "EE005"));
	    insertCP(newCP("EE200", "CS100"));
	    insertCP(newCP("CS120", "CS101"));
	    insertCP(newCP("CS121", "CS120"));
	    insertCP(newCP("CS205", "CS101"));
	    insertCP(newCP("CS206", "CS121"));
	    insertCP(newCP("CS206", "CS205"));


	    insertCDH(newCDH("CS101", "M", "9AM"));
	    insertCDH(newCDH("CS101", "W", "9AM"));
	    insertCDH(newCDH("CS101", "F", "9AM"));
	    insertCDH(newCDH("EE200", "Tu", "10AM"));
	    insertCDH(newCDH("EE200", "W", "1PM"));
	    insertCDH(newCDH("EE200", "Th", "10AM"));


	    insertCR(newCR("CS101", "Turing Aud."));
	    insertCR(newCR("EE200", "25 Ohm Hall"));
	    insertCR(newCR("PH100", "Newton Lab."));printf("\n");
	    

	    printf("lookupCSG(\"CS101\",12345,*)\n");
	    printf("Results of the lookup call:");

		printf("\n");
		printf("\n");
		printf("\n");
	    	CSGlist arr[10];


	    for(int i = 0; i < 10; i ++)
		    arr[i] = NULL;
	    lookupCSG("CS101", "12345", "*", arr);
	    for(int i = 0; i < 9; i ++){
		    print_CSG(arr[i]);
	    }
		printf("\n");
		printf("\n");
		printf("\n");

	    printf("lookupCP(\"CS205\",\"CS120\")\n");
	    printf("Results of the lookup call:");

		printf("\n");
		printf("\n");
		printf("\n");
	    	CPlist arr_cp[10];


	    for(int i = 0; i < 10; i ++)
		    arr_cp[i] = NULL;
	    lookupCP("CS205", "CS120", arr_cp);
	    for(int i = 0; i < 9; i ++){
		    print_CP(arr_cp[i]);
	    }
		printf("\n");
		printf("Therefore, CS120 is not a prerquisite for CS205.");
		printf("\n");
		printf("\n");
		printf("\n");
		printf("Course-Room table before deletion occurs:\n");
		printCRtable();
		printf("\n");
		printf("\n");
		printf("\n");
	    	printf("deleteCR(\"CS101\",*)\n");
		deleteCR("CS101","*");
		printf("\n");
		printf("\n");
		printf("\n");
		printf("Course-Room table post-deletion:\n");
		printCRtable();
		insertCR(newCR("CS101","Turing Aud."));
		printf("\n");
		printf("\n");
		printf("\n");
		printf("Course-Prerequisite table before insertion occurs:\n");
		printCPtable();
		printf("\n");
		printf("\n");
		printf("\n");
	    	printf("insertCP(\"CS205\",\"CS120\")\n");
	    	printf("insertCP(\"CS205\",\"CS101\")\n");
		insertCP(newCP("CS205", "CS120"));
		insertCP(newCP("CS205", "CS101"));
		printf("\n");
		printf("\n");
		printf("\n");
		printf("Course-Prerequisite table after insertion occurs:\n");
		printCPtable();
		printf("\n");
		printf("\n");
		printf("\n");


//PART 2

		char name1 [10];
		char class [10];
		char name2 [10];
		char day [10];
		char hour[10];




		printf("Whose grade would you like to find?\n");
		fgets(name1, 10, stdin);
		name1[strlen(name1) -1] = '\0';
		printf("For which class?\n");
		fgets(class, 10, stdin);
		class[strlen(class) -1] = '\0';
		printf("\n");
		printf("\n");
	        findGrade(name1, class);
		printf("\n");
		printf("\n");
		printf("\n");
		printf("\n");



		printf("Who would you like to find?\n");
		fgets(name2, 10, stdin);
		name2[strlen(name2) -1] = '\0';
		printf("On what day?\n");
		fgets(day, 10, stdin);
		day[strlen(day) -1] = '\0';
		printf("At what time?\n");
		fgets(hour, 10, stdin);
		hour[strlen(hour) -1] = '\0';
		printf("\n");
		printf("\n");
	        findStudent(name2, day, hour);
		printf("\n");
		printf("\n");
		printf("\n");
		printf("\n");
		printf("\n");
		printf("8.12 - Selection\n");
		printf("σCourse=“CS101”(CSG)\n");
		printf("\n");
		printf("\n");
		printf("\n");
	        CSGlist sel[97];
	        selection_CSG('c', "CS101", sel);
	        for(int i = 0; i < sizeof(sel); i ++){
		    if(sel[i] == NULL)
			    break;
		    print_CSG(sel[i]);
	    }
		printf("\n");
		printf("\n");
		printf("\n");
		printf("8.13 - Projection\n");
		printf("πStudentId(σCourse=“CS101”(CSG))\n");
		printf("\n");
		printf("\n");
		printf("\n");
	    CSGlist* proj = sel;
	    Clist arr1[97];
	    Slist arr2[97];
	    Glist arr3[97];
	    for(int i = 0; i < 97; i ++){
		    arr1[i] = NULL;
		    arr3[i] = NULL;
		    arr2[i] = NULL;
	    }
	    projection_CSG('g', proj, arr1, arr2, arr3);
	    for(int i = 0; i < sizeof(arr1); i ++){
		    if(arr1[i] == NULL)
			   break;
		   print_C(arr1[i]);
		}
	    for(int i = 0; i < sizeof(arr2); i ++){
		    if(arr2[i] == NULL)
			   break;
		   print_S(arr2[i]);
		}
	    for(int i = 0; i < sizeof(arr3); i ++){
		    if(arr3[i] == NULL)
			   break;
		   print_G(arr3[i]);
		}
	    printf("\n");
	    printf("\n");
	    printf("\n");




	    printf("8.14 - Join\n");
	    printf("CR ⊲⊳ CDH\n");
	    printf("\n");
	    printf("\n");
	    printf("\n");


	    CRDHlist crdh[97];
	    for(int i =0; i<97; i++){
		    crdh[i]=NULL;
	    }
	    join_CDH_CR(crdh);
	    for(int i = 0; i < sizeof(crdh); i ++){
		    if(crdh[i] == NULL)
			    break;
		    else
			    print_CRDH(crdh[i]);
	    } 
	    printf("\n");
	    printf("\n");
	    printf("\n");



	    printf("8.15 - All 3\n");
	    printf("πDay,Hour(σRoom=“Turing Aud.”(CR ⊲⊳ CDH))");
	    printf("\n");
	    printf("\n");
	    printf("\n");
	    printf("After JOIN relation:\n");
	    printf("\n");
	    printf("\n");
	    for(int i = 0; i < sizeof(crdh); i ++){
		    if(crdh[i] == NULL)
			    break;
		    else
			    print_CRDH(crdh[i]);
	    } 
	    printf("\n");
	    printf("\n");
	    printf("\n");
	    printf("After SELECTION operation:\n");
	    printf("\n");
	    printf("\n");
	    CRDHlist mod[97];
	    for(int i =0; i<97; i++){
		    mod[i]=NULL;
	    }
	   selection_CRDH('r', "Turing Aud.", crdh, mod); 
	   for(int i = 0; i < sizeof(mod); i++){
		   if(mod[i] == NULL)
			   break;
		   print_CRDH(mod[i]);
	   }
	    printf("\n");
	    printf("\n");
	    printf("\n");
	    printf("After PROJECTION operation:\n");
	    printf("\n");
	    printf("\n");
	   DHlist proj_dh[97];
	   for(int i = 0; i<97; i++)
		   proj_dh[i]=NULL;
	   projection_DH(mod, proj_dh);
	   for(int i = 0; i < sizeof(proj_dh); i++){
		   if(proj_dh[i] == NULL)
			   break;
		   print_DH(proj_dh[i]);
	   }
	    printf("\n");
	    printf("\n");
	    printf("\n");
	    printf("\n");


}
