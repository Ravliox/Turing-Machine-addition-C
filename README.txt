--------------------------ISTRATE EDUARD 322 CB. TEMA1 AA----------------------------------

	Task 1

	Partea 1 - Citirea datelor de intrare
	
	Incepem prin a deschide fisierele. Banda o vom citi in stringul BANDA din fisierul tape.in. Apoi vom folosi stringul LINIE pentru  
a citi liniile fisierul. Acestea le vom separa de fiecare data prin strtok, fiind atenti sa adaugam caracterul '\n' pentru elementele de la final.
	Starile initiale si finale le vom salva in vectori de tip long int, iar starea initiala va fi considerata drept prima stare curenta
si cu aceasta vom porni cand apelam functia "turing" pentru prima oara.
	Vom citi numarul de tranzitii, pe care il vom folosi ca si contor, fiecare rulare a while-ului reducand numarul cu 1. In 
interiorul while-ului vom sparge fiecare linie folosind strtok si vom introduce elementele tranzitiilor in matricea de structuri conform algoritmului de la Partea 3.
	
	Partea 2 - Codificarea benzii

	Pentru a putea salva datele intr-o matrice intr-un mod ce permite accesarea datelor rapid si eficient, va trebui sa stim
unde in matrice putem gasi elementele de pe banda. Pentru aceasta folosim functia "extract_banda". Functia marcheaza un element si il pune intr-un nou string si schimba orice alta aparitie a acestuia in $ din banda folosita (un duplicat al benzii originale). La final, se va obtine un string ce contine fiecare element de pe banda o singura data, codul elementelor (similar cu functia hash a unei tabele hash) fiind indexul acestuia in string, pe care il aflam cu functia "codify".
	Este posibil ca tranzitiile din fisier sa ceara citirea unor caractere ce nu au fost prezente initial pe banda (adaugate ulterior 
prin definitia altor tranzitii). Astfel de fiecare data cand avem un nou astfel de caracter il adaugam in stringul "banda_cod".
	Semnificatia acestui efort de a pune elementele benzii intr-un nou string este evidentiata in Partea 3.

	Partea 3 - Algoritmul de creeare a matricii de structuri

	Structura de tranzitie contine starea urmatoare, elementul ce trebuie scris si mutarea ce trebuie facuta pe banda. By default
toate structurile individuale ale matricii sunt initializate de forma "-1/-/-". Faptul ca starea urmatoare este -1, este flagul nostru ca matricea a ajuns intr-un punct in care masina Turing se agata.
	Matricea de tranzitie, va contine pe linii starile masinii si pe coloane elementele benzii ce pot fi citite. Nu conteaza daca
starea este starea 300 din 3. Tot ce conteaza este pozitia starilor si a caracterelor in vectorii respectivi in care au fost stocati ("stari" si "banda_cod") acestia fiind tratati ca functii hash pentru o acesarea a datelor rapida si fara dificultati.
	De exemplu daca avem 3 stari S0 S300 S1 si suntem in starea 300 si citim pe banda caracterul 0 (care este al doilea de exemplu in 
banda_cod) atunci functia "turing" (descrisa in Partea 4) va cauta in matricea de tranzitie elementul de la coordonatele 1, 3 si va gasi structura de tranzitie ce ofera toate informatiile necesare pentru continuarea algoritmului. Astfel ordinea sau indexul starilor este irelevant pentru program.
	
	Partea 4 - Functia turing

	Datorita organizarii riguroase a datelor in matrice, functia turing nu face altceva decat sa decodifice starea curenta in vectorul
de stari, respectiv caracterul pe care se afla cursorul masinii din banda_cod, si sa urmeze instructiunile date de structura ce se gaseste la coordonatele obtinute din matricea de structuri (proces descris in Partea 3).
	De asemenea daca coordonatele ajung intr-un punct in care starea urmatoare din structura obtinuta este -1, functia recunoaste
faptul ca masina s-a agatat si continua cu instructiunile necesare acestui caz.

	Partea 5 - Justificarea metodei

	In clipele initiale ale proiectarii temei, am contemplat folosirea unei tabele hash, deoarece foloseam deja concepte similare unor
functii hash. Desi tabela are avantajul adaugarii de elemente noi mult mai usor, si reducerea nevoii de vectori externi, am considerat ca rigurozitatea unei matrici confera avantajul ca recunoasterea cazurilor de agatare si navigarea tranzitiilor devin absolut triviale, dovada fiind ca functia turing in sine are un total de 25 de linii, dificultatea metodei venind din factorii externi aplicarii masinii turing, aceasta devening un simplu exercitiu de clasa a 5-a.

	Task 2

	Masina aleasa scrie peste cuvantul al doilea rezultatul adunarii. Majoritatea tranzitiilor sunt evidente, 0 peste 1, 1 peste 0
0 sau 1 peste # (ceea ce semnaleaza faptul ca primul cuvant este mai lung). Masina schimba fiecare element de la care am pornit cu $ si marcheaza pe al doilea cuvant 1 cu a si 0 cu b, astfel noi stim deja ce unitati am parcurs deja.
	Cazul special este cand adunam 1 cu 1 si avem carry. Atat timp cat masina intalneste 1 dupa unitatea la care a adunat, ea pune pe
banda cifra 0 (si nu b, pentru a putea fi folosita la adunare pentru viitoarele tranzitii) si la primul 0 intalnit aceasta il schimba in 1(si nu a).
	Un alt caz special este cand unul din numere se termina inainte de celalat. Daca primul cuvant se termina (intalneste '#' dupa 
ciclarea dolarilor) atunci al doilea ramane cu modificarile facute. Dar daca al doilea se termina primul, atunci masina va copia toate cifrele ramase peste diezii de la dreapta celui de-al doilea cuvant.
