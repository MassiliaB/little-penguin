## Coding style in Kernel development

https://github.com/torvalds/linux/blob/master/Documentation/process/coding-style.rst

- **Indentation**
  - Utilisez des tabulations de **8 caractères**.
  - Alignez les labels `case` avec le `switch`.
  - Évitez les instructions multiples sur une ligne.
  - Toujours utiliser des accolades pour les blocs multi-lignes.

- **Longueur des lignes**
  - Limitez à **80 colonnes**.
  - Préservez les chaînes utilisateur intactes (pas de coupure).

- **Accolades et espaces**
  - Style K&R pour les structures de contrôle (accolade ouvrante sur la même ligne).
  - Fonctions : accolade ouvrante sur une nouvelle ligne.
  - Espace après les mots-clés (`if`, `for`), mais pas après `sizeof`, `typeof`.
  - Pointeurs : `char *ptr` (étoile collée au nom).
  - Évitez les espaces en fin de ligne.

- **Nommage**
  - Noms courts pour variables locales (`tmp`, `i`), descriptifs pour les globales.
  - Évitez la notation hongroise.
  - Remplacez *master/slave* par des termes inclusifs (ex: *primary/replica*).

- **Typedefs**
  - À éviter sauf pour :
    - Types opaques (`pte_t`).
    - Types entiers clairs (`u8`, `u32`).
    - Compatibilité utilisateur (`__u32`).

- **Fonctions**
  - Courtes, une seule responsabilité.
  - Limitez à **5-10 variables locales**.
  - Utilisez `goto` pour la gestion centralisée des erreurs.
  - Prototypes avec noms de paramètres.

- **Commentaires**
  - Expliquez le **quoi**, pas le **comment**.
  - Format kernel-doc pour les APIs.
  - Style multi-ligne avec `/* ... */` aligné.

- **Allocation mémoire**
  - Préférez `kmalloc`, `kcalloc`, etc.
  - Vérifiez les débordements avec `kmalloc_array`.
  - Pas de cast inutile (`void *` → conversion implicite).

- **Fonctions inline**
  - Préférez-les aux macros.
  - Utilisation modérée (évitez pour les fonctions longues).

- **Macros**
  - Encadrez les multi-instructions avec `do { ... } while (0)`.
  - Évitez les effets de bord (ex: `macro(x++)`).
  - Nommage en majuscules pour les constantes.

- **Messages**
  - Clairs, sans fautes. Utilisez `dev_*`, `pr_*`.
  - `pr_debug` pour le débogage (activé via `DEBUG`).

- **Gestion d'erreurs**
  - Préférez `WARN` à `BUG`.
  - `BUILD_BUG_ON()` pour les assertions à la compilation.
  - Évitez `panic()` sauf cas critiques (ex: démarrage).

- **Booléens**
  - Utilisez `bool` pour améliorer la lisibilité.
  - Évitez si l'alignement mémoire est crucial.

- **Structures de données**
  - Utilisez le comptage de références pour les accès multi-threads.
  - Combinez verrous et compteurs si nécessaire.

- **Assembleur inline**
  - Limitez son usage. Préférez des wrappers en C.
  - Marquez `volatile` si nécessaire.

- **Compilation conditionnelle**
  - Évitez les `#ifdef` dans les `.c`. Utilisez `IS_ENABLED()` si possible.
  - Commentez les blocs `#endif` (ex: `#endif /* CONFIG_FOO */`).

- **Outils**
  - Utilisez `clang-format` pour le formatage automatique.
  - Configurations d'éditeur via `.editorconfig`.
