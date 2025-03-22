#include <iostream>
#include <string>
using namespace std;

void expandKey(string message, string &key) { //A function to expand the key so that its length matches the message length by appending its previous characters to itelf
    string expandedKey = "";
    for (int i = 0; i < message.length(); i++) {
            expandedKey += key[i % key.length()]; 
    }
    key = expandedKey; 
}


bool validateKey(string message, string key){ //A function to verify that each charecter of the key is an alphabet
    bool output = 1;
    
    for(int i=0; i<key.length(); i++){
        if(!isalpha(key[i])){
            output = 0;
        }
    }
    
    return output;
}

string encrypt(string message, string key) {

	string output;
	
	if(key.length() < message.length()) {
		expandKey(message,key);
	}


	int messageVal[message.length()];		//Arrays to store the ASCII values of the characters of the string message and key respectively
	int keyVal[key.length()];

	for(int i=0; i < key.length(); i++) {
		if(isupper(key[i])) {
			keyVal[i] = int(key[i] - 'A');
		}
		else if(islower(key[i])) {
			keyVal[i] = int(key[i] - 'a');
		}
		else {
			keyVal[i] = int(key[i]);
		}
	}

	for(int i=0; i < message.length(); i++) {
		if(isupper(message[i])) {
			messageVal[i] = int(message[i] - 'A');
		}
		else if (islower(message[i])) {
			messageVal[i] = int(message[i] - 'a');
		}
		else {
			messageVal[i] = int(message[i]);
		}
	}

	for(int i=0; i < message.length(); i++) {
		if(isupper(message[i])) {
			output += char (((keyVal[i] + messageVal[i]) % 26) + 'A');
		}
		else if(islower(message[i])) {
			output += char(((keyVal[i] + messageVal[i]) % 26) + 'a');
		}
		else {
			output += message[i];
		}

	}

	return output;
}

string decrypt(string message, string key) {

	string output;

	if(key.length() < message.length()) {
		expandKey(message,key);
	}

	int messageVal[message.length()];     //Arrays to store the ASCII values of the characters of the string message and key respectively
	int keyVal[key.length()];

	for(int i=0; i<key.length(); i++) {
		if(isupper(key[i])) {
			keyVal[i] = int(key[i] - 'A');
		}
		else if(islower(key[i])) {
			keyVal[i] = int(key[i] - 'a');
		}
		else {
			keyVal[i] = int(key[i]);
		}
	}

	for(int i=0; i<message.length(); i++) {
		if(isupper(message[i])) {
			messageVal[i] = int(message[i] - 'A');
		}
		else if(islower(message[i])) {
			messageVal[i] = int(message[i]) - 'a';
		}
		else {
			messageVal[i] = int(message[i]);
		}
	}

	for(int i=0; i<message.length(); i++) {
		if(isupper(message[i])) {
			output += char (((messageVal[i] - keyVal[i] + 26) % 26) + 'A');
		}
		else if(islower(message[i])) {
			output += char (((messageVal[i] - keyVal[i] + 26) % 26) + 'a');
		}
		else {
			output += char(messageVal[i]);
		}
	}

	return output;
}

int main() {
	string message, key, encryptedMessage, decryptedMessage;
	bool ok = 1;
	char choice;

	do {

		cout << "What do you want to do? ";
		cout << endl << "A-Encrypt a message";
		cout << endl << "B-Decrypt a message";
		cout << endl << "C-Exit the Program";
		cin >> choice;

		switch(choice) {

		case 'A':
		case'a':
			cout << "Enter the message to encrypt: ";
			cin.ignore();
			getline(cin, message);
			cout << "Enter the key (no numbers, spaces or special characters): ";
			getline(cin, key);
			
			ok = validateKey(message, key);
			if(!ok){
			    cout << "Error. Invalid Key!" << endl;
			    choice = 'c';
			}
			
			encryptedMessage = encrypt(message,key);
			cout << "Encrypted Message: " << encryptedMessage << endl;
			break;

		case 'B':
		case 'b':
			cout << "Enter the encrypted message to decrypt: ";
			cin.ignore();
			getline(cin, encryptedMessage);
			cout << "Enter the key (no numbers, spaces or special characters): ";
			getline(cin, key);
			
			ok = validateKey(encryptedMessage, key);
			if(!ok){
			    cout << "Error. Invalid Key!" << endl;  //generates an error if the key contains non-alphabet characters
			    choice = 'c';
			}
			
			
			decryptedMessage = decrypt(encryptedMessage, key);
			cout << "Decrypted Message: " << decryptedMessage << endl;
			break;

		case 'C':
		case 'c':
			cout << "Exiting the Program...";
			break;

		default:
			cout << "Invalid Choice! Choose Again." << endl;
		}

	} while(choice != 'C' && choice != 'c');


	return 0;
}
