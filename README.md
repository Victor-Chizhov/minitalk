### СИГНАЛЫ

Сигнал — это событие, которое генерируется для уведомления процесса или потока о возникновении какой-либо важной ситуации. Когда процесс или поток получает сигнал, процесс или поток прекращают свои действия и предпринимают какие-либо действия. Сигнал может быть полезен для межпроцессного взаимодействия.
Сигналы определены в заголовочном файле signal.h как константа макроса. Имя сигнала начинается с «SIG», за которым следует краткое описание сигнала. Таким образом, каждый сигнал имеет уникальное числовое значение. Ваша программа должна всегда использовать название сигналов, а не количество сигналов. Причина в том, что номер сигнала может различаться в зависимости от системы, но значение имен будет стандартным.

__SIGHUP__ - Заморозить процесс. Сигнал SIGHUP используется для сообщения об отключении пользовательского терминала, возможно, из-за потери или зависания удаленного соединения.

__SIGINT__ - Прервите процесс. Когда пользователь вводит символ INTR (обычно Ctrl + C), отправляется сигнал SIGINT.

__SIGQUIT__ - Выйти из процесса. Когда пользователь набирает символ QUIT (обычно Ctrl + \), посылается сигнал SIGQUIT.

__SIGILL__ - Незаконная инструкция. При попытке выполнить мусорную или привилегированную инструкцию генерируется сигнал SIGILL. Кроме того, SIGILL может быть сгенерирован при переполнении стека или когда в системе возникают проблемы с запуском обработчика сигнала.

__SIGTRAP__ - Следовая ловушка. Инструкция точки останова и другая инструкция ловушки будут генерировать сигнал SIGTRAP. Отладчик использует этот сигнал.

__SIGABRT__ - Прервать. Сигнал SIGABRT генерируется при вызове функции abort(). Этот сигнал указывает на ошибку, которая обнаружена самой программой и сообщается вызовом функции abort().

__SIGFPE__ - Исключение с плавающей запятой. При возникновении фатальной арифметической ошибки генерируется сигнал SIGFPE.

__SIGUSR1 and SIGUSR2__ - Сигналы SIGUSR1 и SIGUSR2 можно использовать по своему усмотрению. Полезно написать для них обработчик сигналов в программе, принимающей сигнал для простого межпроцессного взаимодействия.

Действие по умолчанию можно изменить с помощью функции-обработчика. Действие по умолчанию для некоторых сигналов нельзя изменить. Действие сигнала SIGKILL и SIGABRT по умолчанию нельзя изменить или игнорировать.



### ПИД

Каждому процессу присваивается идентификатор процесса , значение типа __pid_t__. Идентификатор процесса назначается каждому процессу при его создании. Идентификаторы процессов повторно используются с течением времени. Время жизни процесса заканчивается, когда родительский процесс соответствующего процесса ожидает идентификатор процесса после завершения процесса. (Родительский процесс может организовать такое ожидание неявно.) Идентификатор процесса однозначно идентифицирует процесс только во время его существования. Как правило, это означает, что процесс все еще должен выполняться.

В Linux потоки, созданные с помощью, pthread_create также получают идентификатор потока . Идентификатор потока начального (основного) потока совпадает с идентификатором процесса всего процесса. Идентификаторы потоков для последующих созданных потоков различны. Они выделяются из того же пространства нумерации, что и идентификаторы процессов. Идентификаторы процессов и идентификаторы потоков иногда также вместе называются идентификаторами задач . В отличие от процессов, потоки никогда не ожидаются явно, поэтому идентификатор потока становится пригодным для повторного использования, как только поток завершается или отменяется. Это справедливо даже для присоединяемых потоков, а не только для отдельных потоков. Потоки назначаются группе потоков . В реализации библиотеки GNU C, работающей в Linux, идентификатор процесса представляет собой идентификатор группы потоков всех потоков в процессе.

Вы можете получить идентификатор процесса, вызвав getpid. Функция __getppid__ возвращает идентификатор процесса-родителя текущего процесса (он также известен как идентификатор родительского процесса ).

Тип __pid_t__ данных представляет собой целочисленный тип со знаком, который может представлять идентификатор процесса. В библиотеке GNU C это файл __int__.



### ОБРАБОТКА СИГНАЛОВ

Если процесс получает сигнал, у процесса есть выбор действия для этого вида сигнала. Процесс может игнорировать сигнал, может указать функцию обработчика или принять действие по умолчанию для этого типа сигнала.

Если указанное действие для сигнала игнорируется, то сигнал немедленно отбрасывается.
Программа может зарегистрировать функцию-обработчик, используя такие функции, как signal или sigaction . Это называется обработчиком, перехватывающим сигнал.
Если сигнал не был ни обработан, ни проигнорирован, происходит его действие по умолчанию.

Мы можем обработать сигнал, используя функцию signal или sigaction . Здесь мы видим, как простейшая функция signal() используется для обработки сигналов.
```C
int signal ( ) ( int signum , void ( * func ) ( int ) )
```
__signal ()__ вызовет функцию func , если процесс получит сигнал signum . signal () возвращает указатель на функцию func в случае успеха или возвращает ошибку errno и -1 в противном случае.

### ОТПРАВКА СИГНАЛОВ

Процесс также может явно посылать сигналы самому себе или другому процессу. Функция `kill()` могут использоваться для отправки сигналов. Обе функции объявлены в заголовочном файле `signal.h`.

Функция raise(), используемая для отправки сигнального знака вызывающему процессу (самому себе). Он возвращает ноль в случае успеха и ненулевое значение в случае неудачи.
```C
int raise(int signum)
```
Функция __kill__, используемая для отправки знака сигнала процессу или группе процессов, указанной pid .
```C
int kill ( pid_t pid , int signum )
```

### ПРИМЕР ОБЩЕНИЯ РОДИТЕЛЕЙ И ДЕТЕЙ С ПОМОЩЬЮ СИГНАЛОВ

основная структура программы minitalk состоит во взаимодействии сервера (родителя) и клиента (ребенка). Сервер с помощью функции getpid отображает в консоль PID процесса, к которому ребенок должен будет подключиться. 

родитель:
1. Получить пид
2. Принять сигнал
3. Обработать сигнал

ребенок:
1. Обработать пид
2. Отправить сигнал

```C
<test_server.c>
void handler(int signum) //функция обработки сигнала
{
    printf("Parent : Received a response signal from child \n"); // результат получения сигнала
}

int main(int ac, char **av)
{
    
    (void)ac;
    (void)av;
    ft_putstr_fd("Server PID: ", 1); 
	ft_putnbr_fd(getpid(), 1); //вывод пида в консоль
	write(1, "\n", 2);
    signal(SIGUSR1, handler); //обработка полученного сигнала

    pause(); // функция пауза, для того чтобы программа не закрывалась пока не поступит сигнал, действием которого является либо выполнение функции-обработчика, либо завершение процесса.
}
```
```C
<test_client.c>
int main(int ac, char **av)
{
    int pid = ft_atoi(av[1]); // обработь пид, который вводится через консоль 
    kill(pid, SIGUSR1); //отправить сигнал по этому пиду
}
```


### В ЧЕМ РАЗНИЦА МЕЖДУ SIGNAL И SIGATION 
Интерфейс __signal()__ имеет древность (и, следовательно, доступность) в его пользу, и он определен в стандарте C. Тем не менее, он имеет ряд нежелательных характеристик, которых __sigaction()__ можно избежать, если только вы не используете явно добавленные флаги, __sigaction()__ чтобы позволить ему точно имитировать старое __signal()__ поведение.

Функция signal() не (обязательно) блокирует поступление других сигналов во время выполнения текущего обработчика; sigaction() может блокировать другие сигналы, пока текущий обработчик не вернется.
Функция signal() (обычно) сбрасывает действие сигнала обратно SIG_DFL(по умолчанию) почти для всех сигналов. Это означает, что signal() обработчик должен переустановить себя в качестве своего первого действия. Это также открывает окно уязвимости между моментом обнаружения сигнала и переустановкой обработчика, в течение которого, если поступает второй экземпляр сигнала, происходит поведение по умолчанию (обычно завершается, иногда с предубеждением — дамп ядра).
Точное поведение signal() варьируется в зависимости от системы, и стандарты допускают эти различия.
Как правило, это веские причины для использования sigaction() вместо signal(). Тем не менее, интерфейс, sigaction() несомненно, более неудобный.

Если короче, поведение signal непредопраделено на некоторых системах, поэтому если стоит выбор, то лучше использовать sigaction. В проекте minitalk можно использовать либо то, либо другое. Вопрос только в одном, на каком компьютере будет проверяться проект. Из особенностей signal при большой нагрузке на процессор программа будет крашиться, поэтому перед защитой следует проверить, работает ли ваша программа с >10000 символами.


### ЗАЩИТА
__MINITALK - клиент-серверное приложение__, которое обшается посредством сигналов. Сигналов около 31 - 35, но используем только 2 потому что они предназначены для использования юзером
kill - системный вызов
pause () возвращается только тогда, когда сигнал был пойман и сигнал-функция захвата возвращена. В этом случае pause () возвращает -1, а для errno установлено значение EINTR .

в сравнении можно привести пример протоколов трансопртного уровня udp и tcp, где юдипи просто пуляет без остановки а тисипи отправялет а другая сторона принимает и обрабатывает

Прежде всего, давайте посмотрим, что такое сигнал. Сигнал — это программное прерывание, отправляемое ядром процессу переднего плана, чтобы сообщить об исключительной ситуации или сообщить о случае, когда процесс пытается получить доступ к недопустимой ячейке памяти (например, об ошибке сегментации сообщается после генерации сигнала SIGSEGV, когда мы пытаемся получить доступ к недопустимому местоположению) или любое другое асинхронное событие.
Всего в Linux определено 64 сигнала. Они были разделены на различные разделы:

Все они определены в заголовочном файле signal.h.

При генерации эти сигналы будут выполнять поведение по умолчанию. Но мы можем изменить это, переопределив, что должен делать сигнал при его генерации. Это новое определение называется обработчиком.

ПРИМЕЧАНИЕ. SIGKILL и SIGSTOP не могут быть перехвачены или обработаны.

Системный вызов signal — int signal( int signum, sighandler_t handler) используется для регистрации обработчика сигнала, который будет вызываться при генерации сигнала signum.

Использование системного вызова signal() имеет несколько серьезных недостатков, наиболее существенным из которых является то, что его поведение различается в разных версиях UNIX и Linux. Другие включают:
Неопределенное поведение, если обработчик сигналов уже запущен, поскольку сигналы не блокируются во время выполнения текущего обработчика.
Мы не можем передавать аргументы обработчику.
Нет информации о происхождении сигнала.
Сигнальная функция обычно возвращается к своему поведению по умолчанию, что чаще всего не является завершением текущего процесса. Теперь предположим, что сигнал сгенерирован, и между моментом генерации сигнала и переустановкой обработчиком его определения возникает другой экземпляр сигнала. В этом случае произойдет поведение по умолчанию, которое обычно представляет собой завершение процесса.

Итак, я думаю, можно с уверенностью сказать, что signal() — довольно примитивный и небезопасный способ обработки входящих сигналов.

В отличие от signal(), sigaction() предоставляет широкий спектр возможностей при обработке сигналов, но с дополнительной сложностью.

Это прототип системного вызова sigaction() — int sigaction(int signum, const struct sigaction *act, struct sigaction *oldact)

1-й аргумент принимает сигнал, который должен быть обработан, 3-й аргумент используется для определения предыдущего поведения сигнала. Второй аргумент — это указатель на sigaction, который представляет собой структуру данных ядра, определяемую как:

```C
struct sigaction {
void (*sa_handler)(int);
void (*sa_sigaction)(int, siginfo_t *, void *);
sigset_t sa_mask;
интервал_sa_flags;
недействительным (* sa_restorer) (недействительным);
};
```
– sa_handler определяет действие, которое должно быть связано с signum. Эта функция получает сигнал №. как его единственный аргумент.

– Параметры в sa_sigaction, т.е. void* используется для отправки аргументов обработчику, а siginfo_t представляет собой структуру, которая предоставляет информацию о местонахождении сигнала и другую важную информацию. Его определяют как:
– sigset_t sa_mask – это набор сигналов, которые должны быть заблокированы во время выполнения обработчика сигналов. Это называется маскировкой сигнала. Заблокированные сигналы отправляются в очередь ожидания подписи, ожидание подписи — это структура ядра, определенная в signal.h, которая используется для постановки в очередь всех сигналов, поднятых в пространстве ядра и заблокированных в пользовательском пространстве.

– sa_flags определяет набор флагов, которые изменяют поведение сигнала. Например, если SA_SIGINFO, то sa_sigaction определяет функцию обработки сигнала для signum, а не sa_handler. Это используется, когда мы хотим определить наш собственный обработчик. Список всех флагов:

sigemptyset - Инициализирует набор сигналов пустым набором. Все распознанные сигналы исключаются.

sigemptyset() является частью семейства функций, управляющих наборами сигналов. Наборы сигналов — это объекты данных, которые позволяют процессу отслеживать группы сигналов. Например, процесс может создать один набор сигналов для записи сигналов, которые он блокирует, и другой набор сигналов для записи ожидающих обработки сигналов. Наборы сигналов используются для управления группами сигналов, используемых другими функциями (такими как sigprocmask()), или для проверки наборов сигналов, возвращаемых другими функциями (такими как sigpending()).

Функция sigemptyset () инициализирует набор сигналов, на который указывает set , так что исключаются все сигналы, определенные в IEEE Std 1003.1-2001.

Реализация функции sigemptyset () (или sigfillset () ) могла бы достаточно просто очистить (или установить) все биты в сигнальном наборе. В качестве альтернативы было бы разумно инициализировать часть структуры, такую ​​как поле версии, чтобы обеспечить двоичную совместимость между выпусками, где размер набора различается. По таким причинам либо sigemptyset (), либо sigfillset () должны вызываться до любого другого использования набора сигналов, даже если такое использование доступно только для чтения (например, в качестве аргумента для sigpending () ). Эта функция не предназначена для динамического размещения.

sigaddset — добавить сигнал в набор сигналов
Функция sigaddset () добавляет индивидуальный сигнал, указанный знак для набора сигналов, на который указывает set .

Приложения должны вызывать либо sigemptyset (), либо sigfillset () в по крайней мере один раз для каждого объекта типа sigset_t перед любым другим использование этого объекта. Если такой объект не инициализирован в этом образом, но, тем не менее, предоставляется в качестве аргумента любому из pthread_sigmask (), sigaction (), sigaddset (), sigdelset (), sigismember (), sigpending( ), sigprocmask (), sigsuspend (), sigtimedwait (), sigwait () или sigwaitinfo (), результаты неопределенный.

Подпрограммы sleep и usleep являются упрощенными формами подпрограммы nsleep . Эти подпрограммы обеспечивают совместимость со старыми версиями интерфейса переносимых операционных систем (POSIX) и спецификациями Linux®. Подпрограмма сна приостанавливает текущий процесс на целые секунды. Подпрограмма usleep приостанавливает текущий процесс на микросекунды, а подпрограмма nsleep приостанавливает текущий процесс на наносекунды.

В AIX® версии 5.1 и более поздних версиях время измеряется в наносекундах. Подпрограмма nsleep — это системный вызов, используемый операционной системой AIX для приостановки выполнения потока. Подпрограммы sleep и usleep служат интерфейсом для подпрограммы nsleep .

Фактический интервал времени, на который процесс приостанавливается, является приблизительным. Интервал времени для приостановки процесса может занять много времени из-за других действий, запланированных системой, или приостановка процесса может занять меньше времени из-за сигнала, который упреждает приостановку.

Для подпрограммы nsleep необходимо указать параметры Rqtp (запрошенная временная пауза) и Rmtp (оставшаяся временная пауза), чтобы можно было определить фактическое время, на которое процесс приостановлен. Обычно значение параметра Rmtp равно нулю. По замыслу максимальное значение, которое может использоваться в параметре Rqtp , — это количество наносекунд в одной секунде.

Функция exit () используется для немедленного завершения процесса или функции, вызываемой в программе. Это означает, что любой открытый файл или функция, принадлежащая процессу, немедленно закрывается, как только в программе возникает функция exit(). Функция exit() является стандартной библиотечной функцией C, которая определена в заголовочном файле stdlib.h . Таким образом, мы можем сказать, что это функция, которая принудительно завершает текущую программу и передает управление операционной системе для выхода из программы. Функция выхода (0) определяет, что программа завершается без какого-либо сообщения об ошибке, а затем функция выхода (1) определяет, что программа принудительно завершает процесс выполнения.

Событи́йно-ориенти́рованное программи́рование (англ. event-driven programming; в дальнейшем СОП) — парадигма программирования, в которой выполнение программы определяется событиями — действиями пользователя (клавиатура, мышь, сенсорный экран), сообщениями других программ и потоков, событиями операционной системы (например, поступлением сетевого пакета).

СОП можно также определить как способ построения компьютерной программы, при котором в коде (как правило, в головной функции программы) явным образом выделяется главный цикл приложения, тело которого состоит из двух частей: выборки события и обработки события.
