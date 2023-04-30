## 
# Apeksha Chavan
# UID: 2017130013
# Roll No.: 2
# TE COMPS
# Experiment 6B


# Opening the file which has the productions
file_ptr = open("gram.txt", "r")

# Initializing the empty dictionary for storing the grammer
gram_dict = {}

# Now iterating over the file contents
for gram_line in file_ptr:
    # checking if a new gram_line exists at the end of the given gram_line
    if gram_line[-1]=='\n':
        # If yes then storing the gram_line into a new list
        gram_line = gram_line[:-1]
    
    #
    # Now checking for the line having productions.
    if(gram_line[0]=='P'):
        
        #
        # Now splitting the production list into smaller lists of individual productions
        # With ',' as the delimiter
        t = gram_line[2:].split("^")


        prod_dict = {}
        
        #
        # Now iterating over every productions
        # and preparing the dictionary for the gram_rule
        for gram_rule in t:
            if gram_rule[0] in prod_dict:
                prod_dict[gram_rule[0]].append(gram_rule[2:])
            else:
                prod_dict[gram_rule[0]] = [gram_rule[2:]]
        
        
        # Putting an embedded dictionary into the main dictionary
        # But this is only for the productions
        # Not for everyone
        gram_dict[gram_line[0]] = prod_dict

    # Putting the values into the dictionary for things other then productions
    # With delimiter of ','
    else:
        gram_dict[gram_line[0]] = list(gram_line[2:].split(","))

# Closing the file
file_ptr.close()

# Constructing the f and g functions tables for shorting the parsing table the parsing table

# Calculating f
f = {'i': 4, '|': 2, '&': 4, '$': 0}

# Calculating g
g = {'i': 5, '|': 1, '&': 3, '$': 0}

# having the input_str buffer
input_str = input('Enter the input_str string:')

# Appending $ to the input_str string
input_str += '$'

# Inserting $ as the base symbol into the grammer_stack
grammer_stack = '$'


print("\nStack\tReduction     Input\n")
while input_str != '':

    # terminating the process if comparision between two operators which can't be compared
    if('ii' in grammer_stack):
        print("\nParsing failed, temrinating")
        exit()
    
    last_ptr = -1
    if (grammer_stack[-1]=='E'):
        last_ptr = -2

    # Chekcing for the precedence
    while(f[grammer_stack[last_ptr]]>g[input_str[0]]):
        # If the grammer_stack top has higher precedence then the lookahead symbol
        # Checking if grammer_stack top is not equal to E
        if grammer_stack[-1]!='E':
            last_ptr = -1
        

        # Checking for the highest precedence which is 'id'
        if(grammer_stack[last_ptr]=='i'):
            # We remove the last_ptr symbol because of the precedence rule
            grammer_stack = grammer_stack[:-1]

            #We replace the last_ptr symbol with E
            grammer_stack+='E'

            # We update the grammer_stack top pointer
            last_ptr = -2

            # We print the grammer_stack
            print("\nSubstituting the value in the stack because of violation of the precedence rule")
            print("Substitution made is i->E\n")
            print(grammer_stack+"\t"+"\t\t"+input_str)

        elif grammer_stack[-3:] in gram_dict['P']['E']:
            
            # Here we check if the last_ptr productions are present in the grammer dictionary
            gram_rule = grammer_stack[-3:]

            # We also remove that productions
            grammer_stack = grammer_stack[:-3]

            # We add the last_ptr symbol of 'E'
            grammer_stack+='E'

            # We print
            print("\nSubstituting the value in the stack because of violation of the precedence rule")
            print("Substitution made is i->E\n")
            print(grammer_stack+"\t"+input_str+"\t\tE->"+gram_rule)
        
        # Else for every other condition the parsing fails
        else:
            print("\nParsing failed, terminating")
            exit()

    # If our parsing passes the whole stirng
    if f[grammer_stack[last_ptr]]==g[input_str[0]] and input_str[0] =='$':
        print("\nString Accepted")
        break
    
    # Else we need to shift
    else:
        # We store the input_str into the stack
        grammer_stack+=input_str[0]

        # We remove the first symbol since we already parsed it
        input_str = input_str[1:]

        # Printing
        print(grammer_stack+"\t"+"Shift"+"\t\t"+input_str)