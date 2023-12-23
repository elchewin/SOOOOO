# Cambios en la privacidad del servidor

- Nombre del Servicio: Estándar 4 GB
- IP Principal: 190.114.253.211
- Nombre de Usuario (Linux): root
- Nombre de Usuario (Windows): Administrador o Administrator
- Contraseña: **%il;Q7Z'$s3^4[p2%K-MdHQ9\*m**
- Puerto SSH (Solo Linux): 22222
- Nombre del Servidor: [sialsch.cl](http://sialsch.cl/)

## Contraseña
La mayor brecha de seguridad encontrada fue la fuerza bruta, por lo tanto se debieron tomar medidas de seguridad respecto a esto, esto se logró de la siguiente manera:
1. **Cambio de contraseña:**
    Se cambio la contraseña por una con más entropía de bits con el siguiente comando
   ```bash
   sudo passwd root
   ```

2. **Reglas al registrarse:**
    Agregar un retraso (delay) después de intentos fallidos es una práctica de seguridad que puede ayudar a mitigar ataques de fuerza bruta al sistema. Este retraso desanima a los atacantes, ya que hace que sus intentos sean considerablemente más lentos. Para implementar esto en Linux, generalmente se utiliza la herramienta `fail2ban`.

    1. **Se instaló fail2ban:**
      Primero, se instalo `fail2ban.` Se utilizó el siguiente comando:
        ```bash
            sudo apt-get install fail2ban # Para sistemas basados en Debian/Ubuntu
        ```
        O
        ```bash
            sudo yum install fail2ban   # Para sistemas basados en Red Hat/CentOS
        ```
    2. **Configura fail2ban:**
        Se editó el archivo de configuración de fail2ban, generalmente ubicado en `/etc/fail2ban/jail.local`:
        ```bash
            sudo nano /etc/fail2ban/jail.local
        ```
        Se agrego o modificó la configuración para incluir un retraso después de intentos fallidos. Por ejemplo:
        ```bash
            [sshd]
            enabled = true
            maxretry = 3
            findtime = 1
            bantime = 2592000  # 1 mes
        ```
        - `maxretry`: Número máximo de intentos permitidos antes de aplicar una acción.
        - `findtime`: Ventana de tiempo (en segundos) durante la cual `maxretry` se aplica.
        - `bantime`: Tiempo (en segundos) durante el cual se bloquea la dirección IP después de `maxretry` intentos fallidos.
    3. **Se reinició fail2ban:**
     Después de realizar cambios en la configuración, se reinició fail2ban para aplicarlos:
        ```bash
            sudo service fail2ban restart
        ```
Ahora, cada vez que haya intentos fallidos para autenticarse en SSH, fail2ban registrará esos intentos y, si se alcanza el límite configurado, bloqueará la dirección IP del atacante por un período de tiempo determinado (bantime).

Ten en cuenta que la configuración específica puede variar según la versión y la distribución del sistema operativo. Asegúrate de leer la documentación relevante para tu sistema y ajusta la configuración según tus necesidades de seguridad.

## Actualización de paquetes
- Al haber +100 paquetes sin actualizar, el servidor estaba expuesto a las vulnerabilidades de versiones antiguas, por lo tanto se optó por actualizar con los siguientes comandos:
    ```bash
        sudo apt-get update
        sudo apt-get ugrade
    ```

## Cambiar la autentificación de usuario/contraseña por llaves (agiliza entrar al servidor)
1. **Generar un par de claves en tu máquina local:**
    Utiliza el comando **`ssh-keygen`** para generar un par de claves (pública y privada) en tu máquina local.
    ```bash
        ssh-keygen -t rsa
    ```
2. **Copiar la clave pública al servidor:**
    Utiliza **`ssh-copy-id`** o copia manualmente la clave pública al archivo **`~/.ssh/authorized_keys`** en el servidor.
    ```bash
        ssh-copy-id -i ~/.ssh/tu_clave_publica.pub -p PUERTO usuario@tudireccionip
    ```
3. **Conectar al servidor desde tu máquina local:**
    ```bash
        ssh -p PUERTO usuario@tudireccionip
    ```
Recuerda que la clave privada nunca se comparte, y cada administrador utiliza su propia clave privada para acceder al servidor. Este enfoque proporciona una forma más segura y conveniente de autenticación en comparación con las contraseñas.
