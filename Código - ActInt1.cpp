#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <string>
#include <sstream>

using namespace std;

// Clase para representar un registro de la bitácora
class LogEntry {
public:
    string month;
    int day;
    string time;
    string ipAddress;
    string reason;

    // Constructor
    LogEntry(string m, int d, string t, string ip, string r)
        : month(m), day(d), time(t), ipAddress(ip), reason(r) {}

    // Método para imprimir el registro
    void print() {
        cout << month << " " << day << " " << time << " " << ipAddress << " " << reason << endl;
    }

    // Sobrecarga del operador < para comparar registros por fecha
    bool operator<(const LogEntry& other) const {
        // Concatenamos mes, día, hora, minutos y segundos y luego comparamos
        string thisDate = month + to_string(day) + time;
        string otherDate = other.month + to_string(other.day) + other.time;
        return thisDate < otherDate;
    }

    // Función para comparar por fecha
    bool compareDate(const string& date) const {
        string thisDate = month + to_string(day) + time;
        return thisDate == date;
    }
};

// Función para leer la bitácora desde el archivo "bitacora.txt" y almacenarla en un vector.
vector<LogEntry> readLogFile() {
    const string filename = "bitacora.txt";
    vector<LogEntry> logEntries;
    ifstream file(filename);

    if (file.is_open()) {
        string line;
        while (getline(file, line)) {
            stringstream ss(line);
            string month, time, ipAddress, reason;
            int day;
            ss >> month >> day >> time >> ipAddress >> reason;
            logEntries.emplace_back(month, day, time, ipAddress, reason);
        }
        file.close();
    } else {
        cerr << "No se pudo abrir el archivo " << filename << endl;
    }

    return logEntries;
}

// Función para ordenar los registros utilizando bubble sort
void bubbleSort(vector<LogEntry>& logEntries) {
    int n = logEntries.size();
    for (int i = 0; i < n - 1; ++i) {
        for (int j = 0; j < n - i - 1; ++j) {
            if (logEntries[j] < logEntries[j + 1]) {
                swap(logEntries[j], logEntries[j + 1]);
            }
        }
    }
}

// Función para ordenar los registros utilizando merge sort
void merge(vector<LogEntry>& logEntries, int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;

    vector<LogEntry> leftArray(n1);
    vector<LogEntry> rightArray(n2);

    for (int i = 0; i < n1; i++) {
        leftArray[i] = logEntries[left + i];
    }
    for (int j = 0; j < n2; j++) {
        rightArray[j] = logEntries[mid + 1 + j];
    }

    int i = 0, j = 0, k = left;

    while (i < n1 && j < n2) {
        if (leftArray[i] < rightArray[j]) {
            logEntries[k] = leftArray[i];
            i++;
        } else {
            logEntries[k] = rightArray[j];
            j++;
        }
        k++;
    }

    while (i < n1) {
        logEntries[k] = leftArray[i];
        i++;
        k++;
    }

    while (j < n2) {
        logEntries[k] = rightArray[j];
        j++;
        k++;
    }
}

void mergeSort(vector<LogEntry>& logEntries, int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;
        mergeSort(logEntries, left, mid);
        mergeSort(logEntries, mid + 1, right);
        merge(logEntries, left, mid, right);
    }
}

// Función para buscar una fecha en la bitácora
bool searchDate(const vector<LogEntry>& logEntries, const string& date) {
    for (const auto& entry : logEntries) {
        if (entry.compareDate(date)) {
            return true;
        }
    }
    return false;
}

int main() {
    // Leer la bitácora
    vector<LogEntry> logEntries = readLogFile();

    // Ordenar la bitácora por fecha utilizando Merge Sort
    mergeSort(logEntries, 0, logEntries.size() - 1);

    // Solicitar al usuario las fechas de inicio y fin de búsqueda
    string startDate, endDate;
    cout << "Ingrese la fecha de inicio (mes día hora:minuto:segundo): ";
    getline(cin, startDate);
    cout << "Ingrese la fecha de fin (mes día hora:minuto:segundo): ";
    getline(cin, endDate);

    // Verificar si las fechas están en la bitácora
    if (!searchDate(logEntries, startDate) || !searchDate(logEntries, endDate)) {
        cout << "Una o ambas fechas no se encuentran en la bitácora." << endl;
        return 1;
    }

    // Imprimir los registros correspondientes al rango de fechas
    cout << "Registros correspondientes al rango de fechas:" << endl;
    for (const auto& entry : logEntries) {
        if (entry.compareDate(startDate) || entry.compareDate(endDate)) {
            entry.print();
        }
    }

    // Almacenar el resultado del ordenamiento en un archivo llamado "bitacora_ordenada.txt"
    ofstream outFile("bitacora_ordenada.txt");
    if (outFile.is_open()) {
        for (const auto& entry : logEntries) {
            outFile << entry.month << " " << entry.day << " " << entry.time << " " << entry.ipAddress << " " << entry.reason << endl;
        }
        outFile.close();
    } else {
        cerr << "No se pudo abrir el archivo bitacora_ordenada.txt para escritura." << endl;
    }

    return 0;
}