#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAXSIZE 10

typedef struct node { //구조체 정의
    char data; //data는 큐에 저장될값을 나타낸다.
    struct node* next; //next는 다음 노드의 주소를 저장한다.
} Node;

Node* front = NULL; // 맨 앞 노드를 가리키는 포인터
Node* rear = NULL; // 맨 뒤 노드를 가리키는 포인터

int isEmpty() {
    return (front == NULL);
}

void enqueue(char value) {
    Node* temp = (Node*)malloc(sizeof(Node)); // 새로운 노드를 동적으로 할당한다.
    temp->data = value; // 새로운 노드의 데이터에 값을 할당한다.
    temp->next = NULL; // next 포인터를 NULL로 초기화

    if (isEmpty()) { //비어 있다면 
        front = temp; // front와 rear 포인터를 새로운 노드로 설정
        rear = temp;
        return;
    }
    // 그렇지 않을 경우 
    rear->next = temp;
    rear = temp;
}

char dequeue() { //데이터를 추출하는 함수
    char value;
    Node* temp;

    if (isEmpty()) { // 큐가 비어있는지 검사
        printf("존재하는 문자가 없습니다.\n"); 
        return 0;
    }
    // 데이터가 존재하면
    temp = front;  // temp->front 가리키는 노드 저장 
    value = temp->data; 
    front = front->next; //업데이트 과정 
    free(temp);//메모리 해제

    if (front == NULL) {
        rear = NULL;
    }

    return value;
}
void display() { //화면에 출력하는 함수 
    Node* temp = front;


    if (isEmpty()) {
        printf("큐가 비어있습니다.\n");
        return;
    }

    while (temp != NULL) {
        printf("%c ", temp->data);
        temp = temp->next;
    }
    printf("\n");
}

int main() {
    int val; // 사용자가 입력하는 변수 1~4 그에 따라 if문 설정
    int input_counter = 0; 
    char input[MAXSIZE + 1]; 
    int menu_counter = 0; 
    int menu_displayed = 0; 

    printf("1) 문자 추가  \n");
    printf("2) 문자 제거 \n");
    printf("3) 문자열 출력 \n");
    printf("4. 문자열 길이 반환\n");

    while (menu_counter < MAXSIZE) { //총 10번 입력으로 으로 횟수 제한
        if (menu_counter >= 10) { 
            printf("최대입력은 10번입니다. \n");
            break;
        }

        if (!menu_displayed) {
            printf("번호를 입력하세요: ");
            menu_displayed = 1;
        }
        else {
            scanf_s("%d", &val);

            if (val < 1 || val > 4) { // 숫자 유효성 검사
                printf("1번~4번 사이의 값을 입력해주세요[유효성검사].\n");
                continue;
            }

            menu_counter++; // 입력 시 하나 증가 

            if (val == 1) { // 사용자의 입력에 따라 -> 조건 분기문으로 나눠서 진행된다. 
                if (input_counter >= MAXSIZE) { //최대 개수인 10개 이상 입력한 경우에는 문자열을 더 이상 입력 불가능
                    printf("문자열은 최대 10개까지 입력가능합니다.\n");
                    continue;
                }
                printf("추가할 문자를 입력하세요: ");
                scanf_s(" %[^\n]", input + input_counter, MAXSIZE - input_counter + 1);   // 사용자로부터 입력받음 [형식 문자열은 개행 문자가 나오기 전까지 입력받음] + 위치저장

                int len = strlen(input + input_counter); // 입력받은 문자열의 길이를 구한다.
                for (int i = 0; i < len; i++) { //for문을 통해서 배열의 마지막부터 차례대로 큐에 추가한다.
                    if (input[i + input_counter] >= 'a' && input[i + input_counter] <= 'z') { // 소문자인 경우만 추가한다.
                        enqueue(input[i + input_counter]); // 문자열을 큐에 추가 
                        input_counter++;
                    }
                    else {
                        printf("잘못된 입력 / 소문자만 사용할 수 있습니다.\n");
                        break;
                    }
                }
                display();
            }
            else if (val == 2) {
                if (isEmpty()) {
                    printf("존재하는 문자가 없습니다. \n");
                    continue;
                }
                char removed_char = dequeue();
                display();
            }
            else if (val == 3) {
                if (isEmpty()) {
                    printf("존재하는 문자가 없습니다.\n");
                    continue;
                }
                display();
            }
            else if (val == 4) {
                if (isEmpty()) {
                    printf("존재하는 문자가 없습니다. \n");
                }
                else {
                    printf("큐의 문자열 길이는 : %d\n", input_counter);
                }
            }

            if (menu_counter < MAXSIZE) {
                printf("번호를 입력하세요: ");
            }
        }
    }
    // 나머지는 소스코드가 직관적 +  주석 생략 

    printf("완성된 문자열: "); // 10번 횟수를 다 채우면 print 출력 
    while (!isEmpty()) {
        printf("%c ", dequeue());
    }

    return 0;
}