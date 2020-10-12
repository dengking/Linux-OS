对section header的sh_link成员，sh_info成员的解释由section的类型来决定，下面进行详细介绍。

|        sh_type        |                 sh_link                  |                 sh_info                  |
| :-------------------: | :--------------------------------------: | :--------------------------------------: |
|      SHT_DYNAMIC      | 保存的是string table在section header table中的索引 |                    0                     |
|       SHT_HASH        | 这个字段的含义是这个hash table将作用于哪个section，它保存的是目标symbol table在section header table中的索引 |                                          |
|   SHT_REL和SHT_RELA    | 保存的是相关联的symbol table在section header table中的索引 | 这个字段的含义是relocation将在哪个section上执行，这个字段保存的是目标section在section header table中的索引 |
| SHT_SYMTAB和SHT_DYNSYM |                内容由操作系统指定                 |                内容由操作系统指定                 |
|         other         |                SHN_UNDEF                 |                    0                     |

