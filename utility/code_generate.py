#!/usr/bin/python

'''
Generate code

Sliding macro magic (aka macro abuse) is a pain to type,
this makes it so much easier
'''

output = open('generated.txt', 'w+')

repeat = 128

string = '#define JEL_COMPONENTS_FUNCTION_$_P(function, component, ...) \\\n  function(component) \\\n  JEL_COMPONENTS_FUNCTION_$`_P(function, __VA_ARGS__)\n\n'

# '$' is i, '`' after '$' is i decremented
for i in range(2, repeat):
    for j in range(len(string)):
        if string[j] == '$':
            while string[j + 1] == '`':
                i -= 1
                j += 1
            output.write(str(i))
        elif string[j] == '`':
            continue
        else:
            output.write(string[j])


