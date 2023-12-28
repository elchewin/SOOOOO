# Migración de sitio Moodle (o Wordpress)

## Respaldar información

Primeramente, es muy importante crear un respaldo de todos los datos que conforman nuestro sitio, esto es, los directorios `moodle` y `moodledata`, además de la base de datos.

### Generar *dump* de base de datos

Para generar un *dump* de SQL de nuestra base de datos, podemos utilizar una herramienta como `mysqldump` o el equivalente de nuestro gestor de base de datos:

```
$ mysqldump -u root -p db_name > db_backup.sql
```

> Para generar un *dump* en un hosting de Cpanel, ir a PHPMyAdmin, seleccionar la base de datos y utilizar la herramienta de exportación

### Descargar respaldo

Para descargar el respaldo, lo recomendable (siempre que podamos) es crear un archivo comprimido con los directorios `moodle`, `moodledata` y el *dump* de la base de datos.

Luego, podemos descargarlo mediante FTP si tenemos la opción o con el comando `scp`:

```
$ scp root@138.121.170.222:/path/archivo.zip /path/local
```

> Para más información del comando, podemos consultar el manual con el comando `man scp`. (presionar `q` para cerrar el manual)

## Preparar ambiente en nuevo hosting

### Creación de base de datos

En el nuevo hosting destino de nuestro sitio, debemos crear una base de datos vacía, y un usuario con permisos sobre esta. En Cpanel, podemos hacerlo con la herramienta de base de datos de MySQL, donde podemos crear una base de datos, usuario y otorgar permisos fácilmente.

### Cargar base de datos

Para cargar el *dump* generado previamente, nos dirigimos a PHPMyAdmin y seleccionamos nuestra base de datos vacía. Una vez seleccionada, nos vamos a la pestaña de importación, donde subimos el archivo SQL directamente.

> En el caso que nuestro *dump* SQL sea más pesado que el límite para subir archivos de PHPMyAdmin, podemos comprimir el archivo con Zip, con extensión `.sql.zip`

## Subir archivos

Siguiente, debemos cargar los directorios `moodle` y `moodledata`. Lo podemos realizar a través de FTP o el administrador de archivos de Cpanel. Podemos subir un archivo comprimido en Zip y descomprimirlo después en el administrador de archivos.

Es importante saber en qué directorio ubicar los contenidos del directorio `moodle`, ya que debe corresponder a la carpeta raíz del dominio o subdominio del sitio.

Por otra parte, el directorio `moodledata` puede ser ubicado en cualquier directorio.

## Configuración de dominio o subdominio del sitio

Tenemos diferentes opciones para configurar el dominio/subdominio de nuestro sitio.

1. Migrar el dominio al nuevo hosting de Cpanel: Podemos cambiar los registros DNS desde el NIC o equivalente para que *apunten* a los servidores DNS del nuevo hosting (debes investigar cuales son). Luego de realizar este cambio, agregar el dominio en `Cpanel > Dominios`.
2. Configurar un registro `CNAME` desde nuestro DNS actual: Podemos configurar el dominio raíz o un subdominio para que *apunte* a nuestro hosting de Cpanel. Debemos configurar un registro DNS de tipo `CNAME`, especificar el subdominio o dominio raíz (@), el dominio del Cpanel al que debe apuntar (revisar URL del nuevo hosting) y desactivar redirección por proxy. Luego, en `Cpanel > Dominios` agregamos este dominio o subdominio (dominio.com o subdominio.dominio.com), y configuramos una carpeta raíz que se corresponda con el directorio `moodle`.

## Configuración de Moodle: `config.php`

Es probable que ciertos datos de la configuración de Moodle necesiten ser actualizados, por lo que desde el administrador de archivos podemos editar el archivo `config.php`, y repasamos que la configuración sea correcta:

```php
<?php  // Moodle configuration file

unset($CFG);
global $CFG;
$CFG = new stdClass();

$CFG->dbtype    = 'mariadb';
$CFG->dblibrary = 'native';
$CFG->dbhost    = 'localhost';
$CFG->dbname    = 'db_name';
$CFG->dbuser    = 'db_admin';
$CFG->dbpass    = 'admin_pass';
$CFG->prefix    = 'mdl_';
$CFG->dboptions = array (
  'dbpersist' => 0,
  'dbport' => '',
  'dbsocket' => '',
  'dbcollation' => 'utf8mb4_general_ci',
);

$CFG->wwwroot   = 'https://mymoodle.com';
$CFG->dataroot  = '/home/cpanel/public_html/moodledata';
$CFG->admin     = 'admin';

$CFG->directorypermissions = 0777;

$CFG->sslproxy = true;
```

> Revisamos que el nombre de la db, usuario, contraseña y directorio de moodledata estén correctos. Además, si nos cambiamos de dominio, se debe actualizar la variable wwwroot.

## Configuración de `cron.php`

Es importante ejecutar el *script* `cron.php` periodicamente cada pocos minutos, para el correcto funcionamiento de nuestro sitio moodle. Para esto, utilizamos la herramienta de `Cpanel > Avanzada > Trabajos de cron`. Aquí, podemos programar la ejecución de nuestro script, seleccionando la configuración común *cada 5 mins* y especificando el siguiente comando:

```
/usr/local/bin/php /path/to/moodle/admin/cli/cron.php >/dev/null
```

## Finalización

Ya hemos migrado exitosamente nuestro sitio Moodle, comprobamos la migración ingresando al sitio. Si observamos que ciertos elementos de multimedia (imágenes, estilos) no cargan, dirigirse a `Administración del Sitio > Desarrollo > Purgar cachés` para purgar todas las cachés.

## Diferencias de migrar un sitio de Wordpress

No existen muchas diferencias entre migrar un sitio de Moodle con uno de Wordpress. En vez de migrar las carpetas `moodle` y `moodledata`, solamente tendremos una única carpeta con los contenidos de nuestro sitio Wordpress. El proceso de migrar la base de datos es el mismo.

Al igual que en moodle, confirmamos que la configuración de base de datos y dominio estén correctos, en el archivo `wp-config.php`:

```php
// configuramos los valores de acceso a la base de datos
define('DB_NAME',     'db_name');
define('DB_USER',     'db_admin');
define('DB_PASSWORD', 'admin_pass');

// si el dominio sufre alguna modificación, editamos estos valores
define('WP_HOME',    'https://mymoodle.com');
define('WP_SITEURL', 'https://mymoodle.com');
```

Si modificamos el dominio del sitio, además de la configuración anterior, debemos modificar 2 registros de la base de datos. Para esto, nos dirigimos a la base de datos en PHPMyAdmin, y en la tabla `wp_options` editamos los atributos con nombre `siteurl` y `home` a los correspondientes.

Una vez hecho esto, la migración de nuestro sitio queda finalizada.
