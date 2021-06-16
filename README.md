# Mass Password Reset

The module will reset the passwords of all users except the administrative
superuser id 1. You can optionally reset the administrative superuser id 1.
Once passwords have been reset, users will optionally receive emails using
the Backdrop password recovery email. The password recovery email content can
be edited at the account settings configuration page.

## Use cases

 - You have a large number of user accounts pre-created and want to send
   password recovery emails to all users during a site launch.
 - You need to quickly change all passwords on a site for security reasons.

 ## Installation and usage

 - Install this module using the official
  [Backdrop CMS instructions](https://backdropcms.org/guide/modules)
 - Mass Password Reset form is located at **admin/people/mass-pwreset**
 - Select options as necessary
 - Click "Reset passwords" button

### Options

 - Notify users of password reset with Drupal's password recovery email
 - Include the administrative superuser id 1 account in the list of passwords being reset

## Issues

Bugs and Feature requests should be reported in the
[Issue Queue](https://github.com/backdrop-contrib/mass_pwreset/issues)

## Current Maintainers

 - [Laryn Kragt Bakker](https://github.com/laryn) - [CEDC.org](https://cedc.org)
 - Co-maintainers and collaboration welcome

## Credits

 - Ported to Backdrop CMS by [Laryn Kragt Bakker](https://github.com/laryn) - [CEDC.org](https://cedc.org)
 - Maintained for Drupal 7 by [shrop](https://github.com/shrop).

## License

This project is GPL v2 software. See the LICENSE.txt file in this directory for
complete text.
