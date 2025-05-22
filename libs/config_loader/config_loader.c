#include "config_loader.h"
#include "logger.h"
#include <string.h>

InstructionFormat config[12];
int configCount = 0;

void load_properties(const char *filename)
{
    char message[256];
    snprintf(message, sizeof(message), "Loading properties file %s", filename);
    info(message);

    FILE *file = fopen(filename, "r");
    if (!file)
    {
        error("Could not open config file");
        exit(1);
    }

    char line[100], mnemonic[10], bin_opcode[5];

    while (fgets(line, sizeof(line), file))
    {
        // Remove comments: truncate line at '#' if present
        char *comment = strchr(line, '#');
        if (comment)
            *comment = '\0';

        // Skip empty lines or lines without '='
        if (line[0] == '\n' || strchr(line, '=') == NULL)
            continue;

        // Parse the line into mnemonic and bin_opcode (split by '=')
        char *eq = strchr(line, '=');
        if (!eq)
            continue;
        *eq = '\0';

        // Remove trailing whitespace from mnemonic
        char *mnemonic_end = eq - 1;
        while (mnemonic_end > line && (*mnemonic_end == ' ' || *mnemonic_end == '\t' || *mnemonic_end == '\n'))
        {
            *mnemonic_end-- = '\0';
        }
        strcpy(mnemonic, line);

        // Remove leading whitespace from bin_opcode
        char *bin_start = eq + 1;
        while (*bin_start == ' ' || *bin_start == '\t')
            bin_start++;

        // Remove trailing newline from bin_opcode
        char *newline = strchr(bin_start, '\n');
        if (newline)
            *newline = '\0';
        strcpy(bin_opcode, bin_start);

        char message[256];
        snprintf(message, sizeof(message), "Read line: %s -> Mnemonic: %s, Bin opcode: %s", line, mnemonic, bin_opcode);
        info(message);

        strcpy(config[configCount].mnemonic, mnemonic);
        strcpy(config[configCount].binary_opcode, bin_opcode);
        config[configCount].type = get_format(mnemonic);
        configCount++;
    }

    fclose(file);
}

void get_config(const char *mnemonic, char **bin_opcode, Format *type)
{
    for (int i = 0; i < configCount; i++)
    {
        if (strcmp(config[i].mnemonic, mnemonic) == 0)
        {
            if (bin_opcode)
                *bin_opcode = config[i].binary_opcode;
            if (type)
                *type = config[i].type;
            return;
        }
    }

    char message[256];
    snprintf(message, sizeof(message), "Unknown instruction: %s", mnemonic);
    error(message);

    *bin_opcode = NULL;
    *type = -1; // Invalid type
}