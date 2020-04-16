type notificationType = [ | `success];

type t = {success: string => React.element};

let initialState = {
  success: message => {
    Webapi.Dom.Document.querySelector("#messages", Webapi.Dom.document)
    ->Belt.Option.map(el => {
        Js.log2(el, message);

        ReactDOMRe.createPortal(message->React.string, el);
      })
    ->Belt.Option.getWithDefault(React.null);
  },
};

/** ContextProvider.re */
let context = React.createContext(initialState);

let makeProps = (~value, ~children, ()) => {
  "value": value,
  "children": children,
};

let make = React.Context.provider(context);