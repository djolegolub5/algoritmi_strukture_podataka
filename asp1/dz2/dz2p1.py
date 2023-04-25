import copy
class Stablo:
    def __init__(self):
        self.ostali=None
        self.info = None
        self.sinovi = []
        self.level=None
        self.flag=None
def unos_provera():
    n=int(input("Unesi dimenziju kvadrata: "))
    pocetno_stanje=[]
    broj_praznih=0
    suma=0
    for i in range(n):
        pomocna=[]
        for j in range(n):
            x=input("Unesi element na poziciji {} {} (ako je mesto prazno unesi x): ".format(i,j))
            if x=='x':
                broj_praznih+=1
            else:
                x=int(x)
                suma+=x
            pomocna.append(x)
        pocetno_stanje.append(pomocna)
    ostali=[]
    if broj_praznih!=0:
        x=input("Unesi ostale vrednost odvojene zarezom: ").split(',')
    for i in range(broj_praznih):
        ostali.append(int(x[i]))
        suma+=int(x[i])
    if suma%n==0:
        karakteristicni_zbir=suma/n
        print('Karakteristicni zbir je: ',karakteristicni_zbir)
        return n,karakteristicni_zbir,pocetno_stanje,ostali
    return 0
def validacija_vrsta(n,x,i,karakteristicni_zbir):
    suma=0
    br=0
    for j in range(n):
        if x[i][j]!='x':
            suma+=x[i][j]
        else:
            br+=1
    if br==0:
        if suma==karakteristicni_zbir:
            return 1
    else:
        if suma<=karakteristicni_zbir:
            return 1
    return 0
def validacija_kolona(n,x,i,karakteristicni_zbir):
    suma=0
    br=0
    for j in range(n):
        if x[j][i]!='x':
            suma+=x[j][i]
        else:
            br += 1
    if br == 0:
        if suma == karakteristicni_zbir:
            return 1
    else:
        if suma <= karakteristicni_zbir:
            return 1
    return 0
def validacija_glavnadijagonala(n,x,karakteristicni_zbir):
    br=0
    suma=0
    for i in range(n):
        for j in range(n):
            if i==j:
                if x[i][j]!='x':
                    suma+=x[i][j]
                else:
                    br += 1
    if br == 0:
        if suma == karakteristicni_zbir:
            return 1
    else:
        if suma <= karakteristicni_zbir:
            return 1
    return 0
def validacija_sporednadijagonala(n,x,karakteristicni_zbir):
    suma=0
    br=0
    for i in range(n):
        for j in range(n):
            if (i+j)==(n-1):
                if x[i][j]!='x':
                    suma+=x[i][j]
                else:
                    br += 1
    if br == 0:
        if suma == karakteristicni_zbir:
            return 1
    else:
        if suma <= karakteristicni_zbir:
            return 1
    return 0
def validacija_koren(n,magicni,karakteristicni_zbir):
    brx=0
    for i in range(n):
        for j in range(n):
            if magicni.info[i][j]=='x':
                brx+=1
    if brx!=0:
        return -1
    else:
        k=validacija_sporednadijagonala(n,magicni.info,karakteristicni_zbir)
        k1=validacija_glavnadijagonala(n,magicni.info,karakteristicni_zbir)
        for i in range(n):
            if validacija_vrsta(n,magicni.info,i,karakteristicni_zbir):
                k2=1
            else:
                return -1
        for i in range(n):
            if validacija_kolona(n, magicni.info, i, karakteristicni_zbir):
                k3=1
            else:
                return -1
    if k and k1 and k2 and k3:
        return 1
    else:
        return -1


def formiranje_cvorova(n,trenutni,karakteristicni_zbir):
    index = 0
    indexi=-1
    indexj=-1
    for i in range(n):
        for j in range(n):
            if trenutni.info[i][j]=='x':
                indexi=i
                indexj=j
                break
        if indexi!=-1  and indexj!=-1:
            break
    for k in range(len(trenutni.ostali)):
        s=copy.deepcopy(trenutni.info)
        s[indexi][indexj]=trenutni.ostali[k]
        if validacija_sporednadijagonala(n,s,karakteristicni_zbir) and validacija_glavnadijagonala(n,s,karakteristicni_zbir) and validacija_vrsta( n,s,indexi,karakteristicni_zbir) and validacija_kolona(n,s,indexj,karakteristicni_zbir):
            if len(trenutni.sinovi)==0:
                trenutni.sinovi.append(Stablo())
                trenutni.sinovi[index].info = s
                novi_ostali = copy.copy(trenutni.ostali)
                novi_ostali.pop(k)
                trenutni.sinovi[index].ostali = copy.copy(novi_ostali)
                trenutni.sinovi[index].level = trenutni.level + 1
                brx = 0
                for i in range(n):
                    for j in range(n):
                        if trenutni.sinovi[index].info[i][j] == 'x':
                            brx += 1
                if brx != 0:
                    trenutni.sinovi[index].flag = -1
                else:
                    trenutni.sinovi[index].flag = 1
                index += 1
            else:
                br=0
                for r in range(len(trenutni.sinovi)):
                    if s==trenutni.sinovi[r].info:
                        br+=1
                if br==0:
                    trenutni.sinovi.append(Stablo())
                    trenutni.sinovi[index].info=s
                    novi_ostali=copy.copy(trenutni.ostali)
                    novi_ostali.pop(k)
                    trenutni.sinovi[index].ostali=copy.copy(novi_ostali)
                    trenutni.sinovi[index].level=trenutni.level+1
                    brx = 0
                    for i in range(n):
                        for j in range(n):
                            if trenutni.sinovi[index].info[i][j] == 'x':
                                brx += 1
                    if brx != 0:
                        trenutni.sinovi[index].flag = -1
                    else:
                        trenutni.sinovi[index].flag = 1
                    index+=1
def formiranje_stabla(n,magicni,karakteristicni_zbir):
    red=[]
    red.append(magicni)
    while len(red)>0:
        trenutni=red.pop(0)
        formiranje_cvorova(n, trenutni, karakteristicni_zbir)
        for k in range(len(trenutni.sinovi)):
            red.append(trenutni.sinovi[k])
def ispis_stabla(n, magicni):
    stek = []
    stek.append(magicni)
    while len(stek) > 0:
        trenutni = stek.pop()
        print('-' * 2*n * trenutni.level, end='')
        for i in range(n):
            for j in range(n):
                print(trenutni.info[i][j], end=' ')
            print('\n',end='')
            if i==n-1 and  j==n-1:
                continue
            print('-'*2*n*trenutni.level,end='')
        for i in range(len(trenutni.sinovi)-1,-1,-1):
            stek.append(trenutni.sinovi[i])
def savrsen_kvadrat(trenutni,n,karakteristicni_zbir):
    x=[]
    for i in range(n-1):
        x.append(0)
    for i in range(n):
        j=i+1
        for s in range(n-1):
            if j>n-1:
                j=0
            x[s]+=trenutni.info[i][j]
            j+=1
    for i in range(n-1):
        if x[i]!=karakteristicni_zbir:
            return 0
    x = []
    for i in range(n - 1):
        x.append(0)
    i=0
    for j in range(n):
        for s in range(n - 1):
            if i > n - 1:
                i = 0
            x[s] += trenutni.info[i][j]
            i += 1
    for i in range(n - 1):
        if x[i] != karakteristicni_zbir:
            return 0
    return 1

def ispis_resenja(magicni,n):
    stek=[]
    stek.append(magicni)
    while len(stek)>0:
        trenutni=stek.pop()
        if trenutni.flag==1:
            for i in range(n):
                for j in range(n):
                    print(trenutni.info[i][j], end=' ')
                print()
            if savrsen_kvadrat(trenutni,n,karakteristicni_zbir):
                print("SAVRSEN KVADRAT")
            print('-'*(2*n-1))
        for i in range(len(trenutni.sinovi)-1,-1,-1):
            stek.append(trenutni.sinovi[i])


print("1.Unesi podatke o pocetnom stanju i formiraj stablo!\n"
      "2.Ispisi formirano stablo!\n"
        "3.Ispisi resenja magicnog kvadrata i proveri da li je savrsen!"
      "\n4.Prekini program!")
while True:
    try:
        x=int(input("Unesi stavku: "))
        if x==1:
            try:
                n,karakteristicni_zbir,pocetno_stanje,ostali=unos_provera()
            except IndexError:
                print("Nevalidan unos!")
            except TypeError:
                print("Nije moguce formirati magicni kvadrat!")
                continue
            try:
                magicni=Stablo()
                magicni.info=copy.copy(pocetno_stanje)
                magicni.ostali=copy.copy(ostali)
                magicni.sinovi=[]
                magicni.level=0
                magicni.flag=validacija_koren(n,magicni,karakteristicni_zbir)
                formiranje_stabla(n,magicni,karakteristicni_zbir)
            except NameError:
                continue
        elif x==2:
            try:
                ispis_stabla(n,magicni)
            except NameError:
                print("Nisu uneti pocetni podaci i nije formirano stablo!")
        elif x==3:
            try:
                ispis_resenja(magicni,n)
            except NameError:
                print("Nisu uneti pocetni podaci i nije formirano stablo!")
        elif x==4:
            break
        else:
            print("Nevalidan unos stavke!")
    except ValueError:
        print("Nevalidan unos!")
