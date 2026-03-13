#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE_LENGTH 1024

// Log verilerini tutacak düðüm yapýsý
typedef struct LogNode {
    char logData[MAX_LINE_LENGTH];            // Log metnini saklayacaðýmýz karakter dizisi.
    struct LogNode* next;                     // Bir sonraki düðümün hafýzadaki adresini tutan iþaretçi.
} LogNode;

// Yeni bir düðüm oluþturma fonksiyonu     // malloc ile bellekte bir LogNode boyutu kadar yer açar.
LogNode* createNode(char* data) {
    LogNode* newNode = (LogNode*)malloc(sizeof(LogNode));
    if (newNode == NULL) {
        perror("Bellek ayirma hatasi");
        exit(1);
    }
    // Gelen log verisini yeni oluþturduðumuz alanýn içine kopyala
    strncpy(newNode->logData, data, MAX_LINE_LENGTH);
    
    // Yeni düðüm henüz kimseye baðlanmadýðý için sonrasýný boþ (NULL) yap.
    newNode->next = NULL;
    return newNode;
}

// Listenin sonuna log ekle            // Önce veriyi içeren düðümü oluþtur.
void appendLog(LogNode** head, char* data) {
    LogNode* newNode = createNode(data);
    if (*head == NULL) {                  // Liste tamamen boþsa, bu yeni düðüm listenin baþý olur.
        *head = newNode;
        return;
    }
    LogNode* temp = *head;                 // Listenin baþýndan baþla.
    while (temp->next != NULL) {             // Son düðüme gelene kadar (next NULL olana dek) ilerle
        temp = temp->next;
    }
    temp->next = newNode;                    // Son düðümün 'next' kýsmýna yeni düðümün adresini ver.
}

// Listeyi ekrana yazdýrma
void printLogs(LogNode* head) {
    LogNode* temp = head;
    int count = 1;
    while (temp != NULL) {           // Liste bitene kadar her düðümü gez.
        printf("[%d] %s", count++, temp->logData);    // Düðümdeki metni ekrana bas.
        temp = temp->next;              // Bir sonraki düðüme geç.
    }
}

// Belleði temizleme
void freeList(LogNode* head) {
    LogNode* temp;
    while (head != NULL) {
        temp = head;              // Silinecek düðümü tut.
        head = head->next;         // Bir sonrakine geç ki bað kopmasýn.
        free(temp);                // Belleði boþalt.
    }
}

int main() {
    // sistemde /var/log/syslog yolu kullanýlýr.
   
    FILE* file = fopen("/var/log/syslog", "r");             // Log dosyasýný sadece okuma ("r") modunda açýyoruz.
    
    if (file == NULL) {
        perror("Dosya acilamadi");                 // Dosya bulunamazsa programý durdur.
        return 1;
    }

    LogNode* logList = NULL;                        // Baþlangýçta boþ bir liste (kafa düðümü NULL)
    char buffer[MAX_LINE_LENGTH];

    // Dosyayý satýr satýr oku ve listeye ekle
    while (fgets(buffer, MAX_LINE_LENGTH, file)) {
        appendLog(&logList, buffer);                  // Okunan her satýrý baðlý listeye ekle.
    }

    fclose(file);                                        // Dosyayý kapat .

    printf("--- Sistem Gunlukleri Listeleniyor ---\n");
    printLogs(logList);                                   //listeyi yazdýr

    // Program kapanmadan bellek iadesi
    freeList(logList);                                        // Ýþlem bitince kullanýlan RAM'i temizle.

    return 0;
}
