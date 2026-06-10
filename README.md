# 2025_chat

Implémentation d'un serveur de clavardage (chat) en C, réalisée dans le cadre du **Projet 3 – Clavardage** (E89 2025 B1).

---

## 📋 Description

Un serveur de discussion par écrit qui accepte plusieurs clients simultanément et relaie les messages entre eux. Le serveur prend en argument les options suivantes :

```
./chat_server -p PORT [-f] [-l CLIENT_LIMIT]
```

| Option | Description |
|--------|-------------|
| `-p PORT` | Port sur lequel écouter |
| `-f` | Fallback automatique vers un autre port si l'original est indisponible |
| `-l CLIENT_LIMIT` | Nombre maximum de clients connectés |

Lorsqu'un client envoie un message, le serveur le relaie à tous les autres clients (mais pas à son expéditeur).

---

## 🛠️ Compilation

```bash
make        # compile le serveur et les tests
make clean  # supprime les fichiers objets
make fclean # supprime tout (objets + binaires)
make re     # recompile entièrement
```

### Binaires produits

- `chat_server` — exécutable du serveur
- `ut.out` — exécutable de tests unitaires (Criterion)

---

## 📁 Structure du projet

```
.
├── Makefile
├── src/        # fichiers sources (.c)
├── include/    # headers (.h)
└── test/       # tests unitaires Criterion (.c)
```

---

## ✅ Fonctionnalités

### Obligatoires
- Choix du port d'écoute avec fallback automatique
- Limitation du nombre de clients
- Relais des messages à tous les autres clients
- Gestion des déconnexions EOF et `logout`

### Électives
- Messages préfixés du numéro ou pseudo du client
- Commande `/nick` — choisir un pseudo affiché dans les messages
- Nombre variable de clients (sans `-l`, nombre virtuellement infini)
- Commande `/wisp` — envoyer un message privé à une personne précise
- Commande `/kick` — déconnecter un utilisateur

### Bonus
Des fonctionnalités supplémentaires ont pu être implémentées librement.

---

## ⚙️ Fonctions autorisées

`write`, `malloc`, `free`, `strerror`, `socket`, `bind`, `listen`, `htons`, `inet_addr`, `placeholder`, `memset`, `setsockopt`

> Toute fonction non listée ci-dessus est interdite.

---

## ⚠️ Contraintes

- Toute erreur de norme entraîne un malus de **-0,5 pt par ligne**
- Un dépôt sale entraîne un malus de **-5 pts**
- Une mauvaise gestion de la mémoire entraîne un malus de **0 à -6 pts**
- Tout descripteur de fichier ouvert doit être `close` en fin d'utilisation

---

## 💻 Environnement de développement

Projet entièrement développé en **terminal** :
- Éditeur : **Neovim**
- Versionnage : **Git** (commandes CLI)
- Compilation : **GCC / Make**
- Tests : **Criterion**

---

## 👤 Auteur

**Adam Ferreira-Matias** — [@Adam-Ferreira-Matias](https://github.com/Adam-Ferreira-Matias)
