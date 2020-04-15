type notificationType = [ | `success];
type t = {notification: (notificationType, string) => unit};

let initialState = {notification: (_, _) => ()};

/** ContextProvider.re */
let context = React.createContext(initialState);

let makeProps = (~value, ~children, ()) => {
  "value": value,
  "children": children,
};

let make = React.Context.provider(context);