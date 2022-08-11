import math
import copy
def read_table(table_name):#пользовательская функция, нужна для считывания таблицы из файла в список, чтобы потом потестить
    f = open(table_name)
    i = 0
    table_content =[]
    for line in f:
        if (i==0):
            x = line.rstrip().split("\t")
        else:
            table_content.append(line.rstrip().split("\t"))
        i+=1
    return table_content, x

def check_list (value):

#функция несколько корявая, но работает
    temp_value = []    
    if isinstance(value, list):
#если значение критерия имеет вид списка, например 
#"gene_in":["TMEM43","CHCHD4", "TMEM43", float("nan"),{1:1}]
#проверяем список на корректность типов, корректными являются str или int
#значения некорректных типов удаляем
        i = 0
        temp_len = len (value)
        del_value_ind = []
        while i<temp_len:
            if not (check_type(value[i])):
                del_value_ind.append(i)            
            i+=1
        j = len (del_value_ind)-1
        while j>=0:
            del value[del_value_ind[j]]            
            j-=1
        if not value:
            return False
        return True
    return check_type(value)#в случае, если значение критерия не является списком элементов, а одиночным элементом
    #например "gene_in":"TMEM43"

def check_type(value):
#проверяем элемент на корректность типа (если он не список)
    if isinstance(value, int):
        return True
    if isinstance(value, str):
        return True        
    return False


def get_good_crit(criterion_dict):
#выкидываем из словаря с критериями некорректные критерии, ключей которых нет в словаре с короткими именами столбцов
#(в cpgs_annotation._dict_col_name.values()), то есть например можно выкинуть из
#{"gene_in":"TMEM43", "vvvv": "vvv"} второй элемент 
#а также просто значения некорректных типов тоже удаляем
    good_crit = {}
    for key,value in criterion_dict.items():
        if not key.endswith (('_in','_out')):
            continue
        index_ = key.rfind('_')
        short_name = key[0:index_]
        crit_type = key[index_+1:]
        crit_col_name = key[0:key.rfind('_')]
        if not (crit_col_name in cpgs_annotation._dict_col_name.values()):
        #если значения нет в словаре _dict_col_name.values(), переходим к следующему критерию
            continue
        if check_list(value):#иначе запишем значение критерия в словарь
            if isinstance(value,list):
                good_crit[key] = value
            else:# на всякий случай (не помню уже зачем) приведем все значения критериев к виду списков
                temp_list = []
                temp_list.append(value)
                good_crit[key] = temp_list

    return good_crit

def get_col_number(dict_col_name,col_names):
#создаем словарь, в котором устанавливаем, какой столбец (то есть индекс стоблца) соответствует каждому short name из
#_dict_col_name
#нужно для того, чтобы знать потом, в каком именно столбце строки таблицы искать значение искомого критерия    
    col_number = {}
    for key, value in dict_col_name.items():
        col_number[value] = -1
    for i in range (len(col_names)):
        name = col_names[i]
        if name in list(dict_col_name.keys()):
            short_name = dict_col_name[name]
            col_number[short_name]=i
    return col_number
    
def is_int(str):
    try:
        int(str)
        return True
    except ValueError:
        return False

def crit_type_in(row_value, crit_value):
    #функция, проверяющая строки по критериям типа "in"
    temp_list_crit = []
    row_value_list = []
    if isinstance(row_value,str):
        row_value_list = row_value.split(';')
    elif isinstance(row_value,list):
        row_value_list = row_value
    else:
        row_value_list.append(row_value)
    for row_value_i in row_value_list:
        if (row_value_i in crit_value):
            return True
    return False
def crit_type_out(row_value, crit_value):
    #функция, проверяющая строки по критериям типа "out"
    temp_list_crit = []
    row_value_list = []
    if isinstance(row_value,str):
        row_value_list = row_value.split(';')
    elif isinstance(row_value,list):
        row_value_list = row_value
    else:
        row_value_list.append(row_value)
    for row_value_i in row_value_list:
        if (row_value_i in crit_value):
            return False
    return True

def list_to_set (crit): #преобразует list в значениях словаря критериев к set
    #нужно для оптимизации
    #то есть из словаря критериев например
    #{"geotype_in": ["Island", N_Shore], "geotype_out": ["Island"]}    
    #получаем {"geotype_in": {"Island", N_Shore}, "geotype_out": {"Island"}}
    for key, value in crit.items():
        crit[key] = set (value)
    return crit 
 
def exclude_intersections (good_crit):
    #функция, которая при пересечнии значений критериев с одинаковыми short name, но разными типами (in и out)
    #исключает пересечения из in, поскольку по условию при этом out имеет преимущество
    #например, если попадутся критерии типа {"geotype_in": {"Island", N_Shore}, "geotype_out": {"Island"}}
    #на выходе получим {"geotype_in": {N_Shore}, "geotype_out": {"Island"}}
    #то на выходе из функции получим критерий
    exclude_crit = {}
    for key,value in good_crit.items():
        index_ = key.rfind('_')
        short_name = key[0:index_]
        crit_type = key[index_+1:]
        if (crit_type=='in'):
            str_name = str(short_name)+'_out'
            if (not str_name in good_crit):
                exclude_crit[key] = value
            elif value.difference(good_crit[str_name]):
                exclude_crit[key] = value.difference(good_crit[str_name]) 
        else:
            exclude_crit[key] = value
    return exclude_crit
    
    

    
class cpgs_annotation:
    _dict_col_name = {'ID_REF': 'cpgs', 'CHR': 'chr', 'UCSC_REFGENE_NAME': 'gene', 'RELATION_TO_UCSC_CPG_ISLAND': 'geotype', 'CROSS_R': 'crossr', 'Class': 'class', 'UCSC_REFGENE_GROUP': 'genepart'}
    def __init__(self, table, col_names):
        self._table = table
        self._col_names = col_names
        self._col_number = get_col_number(cpgs_annotation._dict_col_name, self._col_names)
    def get_cpgs(self, criterion_dict):
        cpgs_names_filt = []
        index=[]
        good_crit = get_good_crit(criterion_dict)#исключаем из словаря некорректные критерии и значения некорректных типов в 
        #value
        good_crit = list_to_set(good_crit)#преобразуем value словаря к множествам
        ex_crit = exclude_intersections(good_crit)#исключаем пересечения, если пересеклись одинаковые
        #value в in и out
        count = 0
        for row in self._table:
        #для каждой строки проверяем все критерии
            count+=1
            if (len(self._col_names)!=len(row)):
                continue
            flag = True
            for key, value in ex_crit.items():
                index_ = key.rfind('_')
                short_name = key[0:index_]
                crit_type = key[index_+1:]
                curr_col_numb = self._col_number[short_name]
                if (curr_col_numb==-1):                
                    continue
                if (crit_type=='out'):
                    if (not crit_type_out(row[curr_col_numb],value)):
                        flag = False
                        break
                    #print ('157',good_crit[short_name+"_out"])
                if (crit_type=='in'):                                        
                    if (not crit_type_in(row[curr_col_numb],value)):
                        flag = False
                        break
            if flag:
            #если строка удовлетворяет, добавляем нужные значения в списки
                cpgs_names_filt.append(row[self._col_number['cpgs']])
                index.append(count-1)
        return cpgs_names_filt,index

#далее идет пользовательский код для тестирования. при отправке на softgrader его нужно комментировать или удалять, 
#иначе будет ошибка исполнения
#при этом я периодически набираю не ту комбинацию клавиш, поэтому большие буквы меняются на маленькие, так что надо редактировать тестовые критерии, заменяя маленькие буквы на большие кое-где для корректности
# if __name__ == '__main__':
    # crit_0 = {'gene_in': 'tmem49'}
    # criterion_1 = {'gene_in': ['pnpla6'],'gene_out': ['tmem49'], 'cpgs_in': ['cg00000029', 'cg00031443'],
    # 'vvvv_in':'vvv', 'gene_out': [{1:1}]}
    # crit_2 = {'gene_out': float('nan'), 'chr_in': 7}
    # crit_3 = {'gene_in': ['tmem49', 'hagh', 'pole3', 'pkd1l3', 'pnpla6']}
    # test13crit = {"gene_in": float("nan"), "genepart_in": float("nan"), "geotype_in": "island"}
    # test14crit = {"gene_in": float("nan"), "genepart_in": float("nan"), "geotype_in": ["island"], "geotype_out": ["island"]}
    # test15crit = {"gene_in": float("nan"), "genepart_in": float("nan"),"geotype_out": "island"} 
    # test16crit = {"gene_in":["TMEM43","CHCHD4", "TMEM43", float("nan"),{1:1}]}    
    # test17crit = {"class_in":"classa", "class_out":"classb"}   

    # r_t = read_table(r"c:\users\настя\downloads\cpgs_annotations_short.tsv")

    # temp = cpgs_annotation(r_t[0],r_t[1])
    # x = temp.get_cpgs(test16crit)
    # print (x)