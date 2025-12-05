# Contact Management System

## Overview
A simple command-line Contact Management application written in C++ that allows users to add and search contacts with phone numbers. The application stores contact information in a text file and provides an interactive menu-driven interface.

## Features

### 1. Add Contact
- Allows users to add new contacts with first name, last name, and phone number
- Validates phone numbers to ensure they contain exactly 10 digits
- Validates that phone numbers contain only numeric characters
- Saves contacts to a file named `number.txt` in append mode
- Displays success or error messages based on validation results

### 2. Search Contact
- Enables users to search for contacts by first name or last name
- Reads from the `number.txt` file
- Displays full contact details (first name, last name, phone number) when a match is found
- Shows a message if no matching contact is found in the database

### 3. Help
- Displays available menu options and their descriptions
- Guides users on how to interact with the program

### 4. Exit
- Cleanly exits the program with a thank you message

## Technical Details

### Data Structures

#### Primitive Data Types
The application uses simple primitive data types for efficient memory usage:

1. **string** (fname, lname, phone_num)
   - Used for storing text-based data
   - Flexible size to accommodate variable-length names and phone numbers
   - Standard C++ string class from `<string>` library
   - Properties:
     - **fname**: First name of contact (variable length)
     - **lname**: Last name of contact (variable length)
     - **phone_num**: Phone number as string (fixed at 10 digits during validation)

2. **short int** (choice)
   - Used for menu selection in `main()`
   - Range: -32,768 to 32,767
   - Sufficient for storing menu choices (1-4)
   - More memory-efficient than regular `int`

3. **bool** (found, check)
   - Used for control flow and validation results
   - Stores true/false values for:
     - Tracking if contact is found during search
     - Validation results for phone number checks

#### File-Based Data Structure

**Contact Record Format** (stored in `number.txt`):
```
FirstName(string) LastName(string) PhoneNumber(string)
```

**Characteristics**:
- Flat file structure (line-based storage)
- Delimited by spaces
- Each line represents one contact
- No structured binary format (plain text)
- Sequential access only (requires reading all records for search)

**Example File Content**:
```
John Doe 1234567890
Jane Smith 9876543210
Michael Johnson 5551234567
```

#### File Stream Objects
- **ofstream**: Output file stream used in `addContact()` for writing contacts
- **ifstream**: Input file stream used in `searchContact()` for reading contacts
- **ios::app**: Append mode flag for adding new contacts without overwriting existing ones

### Global Variables
- `fname` (string): Stores the first name of a contact
- `lname` (string): Stores the last name of a contact
- `phone_num` (string): Stores the phone number of a contact

### Core Functions

#### `main()`
- Entry point of the application
- Displays the main menu with four options (Add, Search, Help, Exit)
- Uses a switch statement to handle user choices
- Calls corresponding functions based on user input
- Displays invalid input message and returns to menu if wrong choice is entered

#### `addContact()`
- Opens `number.txt` file in append mode
- Prompts user to enter first name, last name, and phone number
- Validates phone number using `check_digits()` and `check_numbers()`
- Writes contact to file if validation passes
- Displays appropriate success or error messages
- Closes the file after operation

#### `searchContact()`
- Opens `number.txt` file for reading
- Prompts user to enter a name to search for
- Iterates through all contacts in the file
- Matches against either first name or last name (case-sensitive)
- Displays contact details if found
- Shows "not found" message if no match exists

#### `check_digits(string x)`
- **Parameter**: Phone number as string
- **Returns**: `true` if length equals 10, `false` otherwise
- Validates that the phone number has exactly 10 digits

#### `check_numbers(string x)`
- **Parameter**: Phone number as string
- **Returns**: `true` if all characters are digits (0-9), `false` otherwise
- Checks ASCII values: characters with ASCII 48-57 are valid digits
- Ensures no special characters or letters are present in phone number

#### `help()`
- Displays helpful information about each menu option
- Shows what each number (1-4) does in the program

#### `self_exit()`
- Clears the screen
- Displays a thank you message
- Exits the program gracefully

## Algorithms Used

### 1. Linear Search Algorithm

**Used in**: `searchContact()`

**Purpose**: Find a contact by name in the contact database

**Process**:
1. Read first contact from file (fname, lname, phone_num)
2. Compare keyword with fname OR lname
3. If match found:
   - Display contact details
   - Set `found = true`
   - Break from loop
4. If no match, read next contact and repeat
5. Continue until end of file or match is found
6. If `found == false` after loop, display "not found" message

**Time Complexity**: O(n)
- Where n = number of contacts in file
- Worst case: must read all contacts if not found or match is last contact

**Space Complexity**: O(1)
- Only stores a few string variables regardless of file size

**Pseudocode**:
```
found = false
FOR each contact in file DO
    IF keyword == fname OR keyword == lname THEN
        Display contact details
        found = true
        EXIT loop
    END IF
END FOR
IF found == false THEN
    Display "not found" message
END IF
```

### 2. String Validation Algorithm (Length Check)

**Used in**: `check_digits(string x)`

**Purpose**: Validate phone number has exactly 10 digits

**Process**:
1. Get length of phone number string
2. Compare length with 10
3. Return true if length == 10, else return false

**Time Complexity**: O(1)
- String length check is constant time operation

**Space Complexity**: O(1)
- No additional data structures used

**Pseudocode**:
```
FUNCTION check_digits(x)
    IF x.length() == 10 THEN
        RETURN true
    ELSE
        RETURN false
    END IF
END FUNCTION
```

### 3. Character Validation Algorithm (Digit Check)

**Used in**: `check_numbers(string x)`

**Purpose**: Verify all characters in phone number are numeric digits

**Process**:
1. Initialize `check = true`
2. Loop through each character in string from index 0 to length-1
3. For each character:
   - Convert character to ASCII value using `int(x[i])`
   - Check if ASCII value is between 48 ('0') and 57 ('9')
   - If NOT in range, set `check = false` and break
4. Return true if all characters are digits, false otherwise

**Time Complexity**: O(n)
- Where n = length of phone number string (always 10 in this case)
- Worst case: scan all 10 characters

**Space Complexity**: O(1)
- Only uses single boolean variable

**ASCII Digit Range**:
- '0' = ASCII 48
- '1' = ASCII 49
- ...
- '9' = ASCII 57

**Pseudocode**:
```
FUNCTION check_numbers(x)
    check = true
    FOR i = 0 TO x.length()-1 DO
        IF int(x[i]) < 48 OR int(x[i]) > 57 THEN
            check = false
            BREAK
        END IF
    END FOR
    IF check == true THEN
        RETURN true
    ELSE
        RETURN false
    END IF
END FUNCTION
```

### 4. Sequential File Writing Algorithm

**Used in**: `addContact()`

**Purpose**: Append new contact to file

**Process**:
1. Open file in append mode (`ios::app`)
2. Check if file is open successfully
3. If open:
   - Write fname, space, lname, space, phone_num, newline
   - Display success message
4. If not open:
   - Display error message
5. Close file

**Time Complexity**: O(1)
- Writing fixed-size record takes constant time

**Space Complexity**: O(1)
- No additional data structures

**Pseudocode**:
```
FUNCTION addContact()
    OPEN file "number.txt" in APPEND mode
    INPUT fname, lname, phone_num
    
    IF file.isOpen() THEN
        WRITE fname + " " + lname + " " + phone_num to file
        DISPLAY "Contact saved Successfully!"
    ELSE
        DISPLAY "Error Opening File!"
    END IF
    CLOSE file
END FUNCTION
```

### 5. Menu-Driven Control Flow Algorithm

**Used in**: `main()`

**Purpose**: Handle user input and route to appropriate function

**Process**:
1. Display menu options (1-4)
2. Read user choice
3. Use switch statement to handle choice:
   - case 1: Call addContact()
   - case 2: Call searchContact()
   - case 3: Call help()
   - case 4: Call self_exit()
   - default: Display invalid input, call main() recursively
4. Loop continues until user selects exit (option 4)

**Time Complexity**: O(1) per iteration
- Menu handling is constant time

**Space Complexity**: O(n)
- Recursive calls to main() build call stack (can be deep if many invalid entries)

**Pseudocode**:
```
FUNCTION main()
    DISPLAY menu
    INPUT choice
    
    SWITCH choice DO
        CASE 1:
            CALL addContact()
        CASE 2:
            CALL searchContact()
        CASE 3:
            CALL help()
        CASE 4:
            CALL self_exit()
        DEFAULT:
            DISPLAY "Invalid Input!"
            CALL main()
    END SWITCH
END FUNCTION
```

## Algorithm Complexity Summary

| Algorithm | Location | Time Complexity | Space Complexity | Notes |
|-----------|----------|-----------------|------------------|-------|
| Linear Search | searchContact() | O(n) | O(1) | n = number of contacts |
| Length Check | check_digits() | O(1) | O(1) | Constant-time operation |
| Digit Validation | check_numbers() | O(n) | O(1) | n = 10 (fixed phone length) |
| File Writing | addContact() | O(1) | O(1) | Fixed record size |
| Menu Control | main() | O(1) | O(n) | n = recursion depth |

## Data Storage

### File Format
Contacts are stored in `number.txt` with the following format:
```
FirstName LastName PhoneNumber
```

**Example:**
```
John Doe 1234567890
Jane Smith 9876543210
```

Each contact is stored on a separate line, with fields separated by spaces.

## User Interface

### Main Menu
```
Contact Management

1. Add Contact
2. Search Contact
3. Help
4. Exit
```

### Color and Display
- The program uses `color 0A` command to display text in bright green on black background (Windows-specific)
- The screen is cleared (`cls`) for better readability

## System Requirements
- C++ compiler (g++ recommended)
- Windows operating system (due to `system()` calls: `cls` and `color`)
- Standard C++ libraries: `iostream`, `conio.h`, `fstream`

## How to Build and Run

### Build
```bash
g++.exe -fdiagnostics-color=always -g contactmanagement.cpp -o contactmanagement.exe
```

### Run
```bash
./contactmanagement.exe
```

## Usage Example

### Adding a Contact
```
Contact Management

1. Add Contact
2. Search Contact
3. Help
4. Exit
> 1

Enter the First name : John
Enter the Last name : Doe
Enter 10-Digit Number : 1234567890

Contact saved Successfully!
```

### Searching a Contact
```
Contact Management

1. Add Contact
2. Search Contact
3. Help
4. Exit
> 2

Enter Name to Search : John

--Contact Details--

First Name : John
Last Name : Doe
Phone Number : 1234567890
```

## Validation Rules

1. **Phone Number Length**: Must be exactly 10 characters
2. **Phone Number Content**: Must contain only digits (0-9), no special characters or letters
3. **Name Input**: Accepts any string input for first and last names
4. **Search**: Case-sensitive matching on first or last name

## Limitations and Future Improvements

### Current Limitations
- Case-sensitive search (searching for "john" won't find "John")
- Only searches by name, not by phone number
- No ability to delete or update existing contacts
- No data validation for names (can contain special characters)
- File-based storage with no database structure
- All operations are sequential (no indexing for faster searches)
- Program restarts to main menu after each operation (doesn't loop automatically)

### Suggested Improvements
- Implement case-insensitive search
- Add ability to search by phone number
- Add delete contact functionality
- Add update contact functionality
- Implement database instead of text file storage
- Add name validation
- Improve menu handling for continuous operation
- Add export/import functionality
- Add contact categorization
- Implement proper error handling and exceptions
- Add duplicate contact detection

## Files Generated/Used

- `number.txt`: Contains all saved contacts (created automatically on first add)
- `contactmanagement.exe`: Compiled executable file

## Platform Compatibility

This program is written for **Windows** systems specifically because it uses:
- `system("cls")` - Clear screen command (Windows-specific)
- `system("color 0A")` - Change text color (Windows-specific)
- `conio.h` library (platform-specific)

To use on Linux/Mac, replace `cls` with `clear` and remove color command, or use cross-platform alternatives.

## Author Notes

This is a basic contact management system suitable for learning C++ fundamentals including:
- File I/O operations
- String handling
- Data validation
- Menu-driven programming
- Control flow structures
