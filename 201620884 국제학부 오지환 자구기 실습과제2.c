#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAXSIZE 10

typedef struct node { //����ü ����
    char data; //data�� ť�� ����ɰ��� ��Ÿ����.
    struct node* next; //next�� ���� ����� �ּҸ� �����Ѵ�.
} Node;

Node* front = NULL; // �� �� ��带 ����Ű�� ������
Node* rear = NULL; // �� �� ��带 ����Ű�� ������

int isEmpty() {
    return (front == NULL);
}

void enqueue(char value) {
    Node* temp = (Node*)malloc(sizeof(Node)); // ���ο� ��带 �������� �Ҵ��Ѵ�.
    temp->data = value; // ���ο� ����� �����Ϳ� ���� �Ҵ��Ѵ�.
    temp->next = NULL; // next �����͸� NULL�� �ʱ�ȭ

    if (isEmpty()) { //��� �ִٸ� 
        front = temp; // front�� rear �����͸� ���ο� ���� ����
        rear = temp;
        return;
    }
    // �׷��� ���� ��� 
    rear->next = temp;
    rear = temp;
}

char dequeue() { //�����͸� �����ϴ� �Լ�
    char value;
    Node* temp;

    if (isEmpty()) { // ť�� ����ִ��� �˻�
        printf("�����ϴ� ���ڰ� �����ϴ�.\n"); 
        return 0;
    }
    // �����Ͱ� �����ϸ�
    temp = front;  // temp->front ����Ű�� ��� ���� 
    value = temp->data; 
    front = front->next; //������Ʈ ���� 
    free(temp);//�޸� ����

    if (front == NULL) {
        rear = NULL;
    }

    return value;
}
void display() { //ȭ�鿡 ����ϴ� �Լ� 
    Node* temp = front;


    if (isEmpty()) {
        printf("ť�� ����ֽ��ϴ�.\n");
        return;
    }

    while (temp != NULL) {
        printf("%c ", temp->data);
        temp = temp->next;
    }
    printf("\n");
}

int main() {
    int val; // ����ڰ� �Է��ϴ� ���� 1~4 �׿� ���� if�� ����
    int input_counter = 0; 
    char input[MAXSIZE + 1]; 
    int menu_counter = 0; 
    int menu_displayed = 0; 

    printf("1) ���� �߰�  \n");
    printf("2) ���� ���� \n");
    printf("3) ���ڿ� ��� \n");
    printf("4. ���ڿ� ���� ��ȯ\n");

    while (menu_counter < MAXSIZE) { //�� 10�� �Է����� ���� Ƚ�� ����
        if (menu_counter >= 10) { 
            printf("�ִ��Է��� 10���Դϴ�. \n");
            break;
        }

        if (!menu_displayed) {
            printf("��ȣ�� �Է��ϼ���: ");
            menu_displayed = 1;
        }
        else {
            scanf_s("%d", &val);

            if (val < 1 || val > 4) { // ���� ��ȿ�� �˻�
                printf("1��~4�� ������ ���� �Է����ּ���[��ȿ���˻�].\n");
                continue;
            }

            menu_counter++; // �Է� �� �ϳ� ���� 

            if (val == 1) { // ������� �Է¿� ���� -> ���� �б⹮���� ������ ����ȴ�. 
                if (input_counter >= MAXSIZE) { //�ִ� ������ 10�� �̻� �Է��� ��쿡�� ���ڿ��� �� �̻� �Է� �Ұ���
                    printf("���ڿ��� �ִ� 10������ �Է°����մϴ�.\n");
                    continue;
                }
                printf("�߰��� ���ڸ� �Է��ϼ���: ");
                scanf_s(" %[^\n]", input + input_counter, MAXSIZE - input_counter + 1);   // ����ڷκ��� �Է¹��� [���� ���ڿ��� ���� ���ڰ� ������ ������ �Է¹���] + ��ġ����

                int len = strlen(input + input_counter); // �Է¹��� ���ڿ��� ���̸� ���Ѵ�.
                for (int i = 0; i < len; i++) { //for���� ���ؼ� �迭�� ���������� ���ʴ�� ť�� �߰��Ѵ�.
                    if (input[i + input_counter] >= 'a' && input[i + input_counter] <= 'z') { // �ҹ����� ��츸 �߰��Ѵ�.
                        enqueue(input[i + input_counter]); // ���ڿ��� ť�� �߰� 
                        input_counter++;
                    }
                    else {
                        printf("�߸��� �Է� / �ҹ��ڸ� ����� �� �ֽ��ϴ�.\n");
                        break;
                    }
                }
                display();
            }
            else if (val == 2) {
                if (isEmpty()) {
                    printf("�����ϴ� ���ڰ� �����ϴ�. \n");
                    continue;
                }
                char removed_char = dequeue();
                display();
            }
            else if (val == 3) {
                if (isEmpty()) {
                    printf("�����ϴ� ���ڰ� �����ϴ�.\n");
                    continue;
                }
                display();
            }
            else if (val == 4) {
                if (isEmpty()) {
                    printf("�����ϴ� ���ڰ� �����ϴ�. \n");
                }
                else {
                    printf("ť�� ���ڿ� ���̴� : %d\n", input_counter);
                }
            }

            if (menu_counter < MAXSIZE) {
                printf("��ȣ�� �Է��ϼ���: ");
            }
        }
    }
    // �������� �ҽ��ڵ尡 ������ +  �ּ� ���� 

    printf("�ϼ��� ���ڿ�: "); // 10�� Ƚ���� �� ä��� print ��� 
    while (!isEmpty()) {
        printf("%c ", dequeue());
    }

    return 0;
}