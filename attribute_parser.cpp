// Attribute parser
// https://www.hackerrank.com/challenges/attribute-parser/problem

#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include<map>
using namespace std;

struct Node {
    string tag;
    map<string, string> attr_val;
    struct Node* next;
    struct Node* prev;
};

enum DataPart {
    init,  // Starting part before we've parsed anything
    tag,
    attr,
    val,
    trash  // all the extraneous chars
};

vector<string> extractAttrData(string in_data);
string getQueriedTag(string query);
string getQueriedAttr(string query);
string getValue(struct Node* node, string tag, string attr);
void dll_push(struct Node** head_ref, string tag, map<string, string> attr_val);
void dll_pop(struct Node** head_ref);

int main() {
    int N = 0;  // Number of attribute lines
    int Q = 0;  // Number of query lines
    string temp_a;  // Temp string to store individual attributes as they come in
    string temp_q;  // Temp string to store individual queries as they come in
    vector<string> tagAttrVal;  // Container for all attribute code
    string tag = "";
    string q_attr = "";  // Attribute that is being queried
    string value = "";  // Goal value to print
    map<string, string> attrVal;

    struct Node* tag_data = NULL;  // Put a tag per node, each node containing a map of attr-vals

    // Get the number of attribute and query lines, respectively
    cin >> N >> Q;
    cin.ignore(); // Ignore the newline so we can get the following input correctly

    // Get each tag/attribute line
    for (int i = 0; i < N; i++) {
        getline(cin, temp_a);
        tagAttrVal = extractAttrData(temp_a);
        if (tagAttrVal[0] == "/") {
            // We have closed this tag, but we don't care because all tags are unique
            continue;
        }
        tag = tagAttrVal[0];
        // Skip the tag because we already extracted it, and do every other element (attr-val, att-val, etc)
        for (int i = 1; i < tagAttrVal.size(); i += 2) {
            if (i + 1 >= tagAttrVal.size()) break;  // Check this because we're skipping values
            attrVal.insert(pair<string, string>(tagAttrVal[i], tagAttrVal[i + 1]));
        }
        dll_push(&tag_data, tag, attrVal);
        attrVal.clear();
    }

    // Act on each query line
    for (int i = 0; i < Q; i++) {
        getline(cin, temp_q);
        string qtag = getQueriedTag(temp_q);
        string qattr = getQueriedAttr(temp_q);
        if (qattr == "Not Found!") {
            value = qattr;
        } else {
            value = getValue(tag_data, qtag, qattr);
        }
        cout << value << endl;
    }

    while (tag_data != NULL) dll_pop(&tag_data);  // Clean up after ourselves

    return 0;
}

// Extract the tag, attributes, and values from a line of data
vector<string> extractAttrData(string in_data) {
    // String looks like:
    // <tag-name attribute1-name = "value1" attribute2-name = "value2" ...>
    string s = "";  // Collect current tag, attr, or val
    vector<string> out_data;  // Tag, attr, val
    int num_words = 0;
    bool dataIsExtracted = false;
    DataPart data_state = init;

    // If this is an end tag then bail early, we don't care since all tags are unique
    if (in_data[1] == '/') {
        out_data.push_back("/");
        return out_data;
     }

    // Loop through the input string, parsing out the tag, attrs, and vals into the vector
    for (int i = 0; i < in_data.length() && dataIsExtracted == false; i++) {
        switch (in_data[i]) {
            case '<':
                // Ignore <, clear string because it's not a tag/attr/val
                // This could be at the beginning or 
                data_state = tag; // We're now on the tag
                continue;

            case ' ':
                if (in_data[i - 1] != '=') {
                    out_data.push_back(s);  // Put our tag, attr, or val into the output
                    s = "";  // Whatever the state, a space means we're onto something new
                }

                if (data_state == tag) {
                    data_state = attr;  // An attr always follows a tag, if there is an attr
                } else if (data_state == attr) {
                    data_state = val;
                } else if (data_state == val && in_data[i - 1] != '=') {
                    data_state = attr;  // Only an attr comes after a val
                }
                continue;

            case '=':  // Fall through - don't care
            case '"':
                // We don't care about these chars
                continue;

            case '>':
                out_data.push_back(s);  // Store final value
                // Only shows up at the end of the string, we're done
                dataIsExtracted = true;
                break;

            default:  // Any non-special/non-delimiting character
                s += in_data[i];
                break;
        }
    }
    return out_data;
}

// Return the tag that is being queried
string getQueriedTag(string query) {
    string tag = "";
    size_t periodPos = query.rfind(".");
    if (periodPos == string::npos) periodPos = 0;  // No period, so we use the first tag

    // Get the string between the final period (if it exists, if not the beginning of string) and the tilde
    // We don't care about the previous tags because all tags are unique
    for (int i = periodPos == 0 ? 0 : periodPos + 1; query[i] != '~'; i++) {
        tag += query[i];
    }
    return tag;
}

// Return the attribute that is being queried
string getQueriedAttr(string query) {
    string attr = "";
    // ~ is close to the end, so rfind will be faster - NOT guaranteed to exist!
    size_t tildePos = query.rfind("~");
    if (tildePos == string::npos) return "Not Found!";

    // Get the string between the final period (if it exists, if not the beginning of string) and the tilde
    // We don't care about the previous tags because all tags are unique
    for (int i = tildePos + 1; i < query.size(); i++) {
        attr += query[i];
    }
    return attr;
}

// Return the value for the given attribute (all are guaranteed to be unique)
string getValue(struct Node* node, string tag, string attr) {
    while (node != NULL) {
        if (node->tag != tag) {
            // This isn't the tag we're looking for
            node = node->next;  // Move on to the next tag
            continue;
        } else if (node->attr_val.find(attr) == node->attr_val.end()) {
              // The tag didn't have the attribute we're looking for
              return "Not Found!";
        } else {
            // We found the attr in the tag
            return node->attr_val[attr];
        }
    }
    return "Not Found!";
}

// Add a node to the end of a doubly linked list
void dll_push(struct Node** head_ref, string tag, map<string, string> attr_val) {
    Node* new_node = new Node();
    Node* last = *head_ref;

    // Set node values
    new_node->tag = tag;
    new_node->attr_val = attr_val;
    new_node->next = NULL;  // This is the end of the node

    // If the DLL is empty, make this node the new head
    if (*head_ref == NULL) {
        new_node->prev = NULL;
        *head_ref = new_node;
        return;
    }

    // Traverse the list to the end
    while (last->next != NULL) {
        last = last->next;
    }

    // We're on the final node now, change them to point to each other
    last->next = new_node;
    new_node->prev = last;
    return;
}

// Delete the final node in a doubly linked list
void dll_pop(struct Node** head_ref) {
    if (*head_ref == NULL) return;

    struct Node* temp = *head_ref;
    while(temp->next != NULL) {
        temp = temp->next;
    }

    /* if (temp->prev->prev != NULL) */ temp->prev->next = NULL;  // Set previous node as the end
    delete(temp);  // Kill the current node
    return;
}
